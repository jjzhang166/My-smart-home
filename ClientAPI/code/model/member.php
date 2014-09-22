<?php
if (!defined('ROOT')) exit('SmartHome');
/*
 * 模块：用户相关
 * @package Model
*/
class member_model extends base {
	static private $_instance=NULL;
	static public function getInstance () {
		if (!self::$_instance) self::$_instance=new self;
		return self::$_instance;
	}
	public function __construct () {
		parent::init();
	}
	//进行登录，检查用户名和密码
	public function onlogin () {
		$user=getgpc('user','P');
		$pwd=getgpc('password','P');
		$pwd=pwdcode($pwd); //对密码进行加密运算
		if (empty($user) || empty($pwd)) return array('success'=>0,'errcode'=>100,'errmsg'=>'Parameter error');
		$one=$this->sql->GetOne('select','user',array(row=>'*','where'=>array(array('name'=>'name','type'=>'eq','val'=>$user))));
		if ($one===FALSE) return array('success'=>0,'errcode'=>2,'errmsg'=>'User not exists');
		if ($one['password']==$pwd) { //登录成功，生成Auth
			$auth=join('|',array($one['id'],$_SERVER['REMOTE_ADDR'],$one['email'],microtime(TRUE)));
			$auth=md5($auth);
			$this->sql->query('addauth','insert','auth',array('insert'=>array('row'=>array('auth','uid','overdue'),'val'=>array($auth,$one['id'],date('Y-m-d',strtotime('+3 Month'))))));
			return array('success'=>1,'auth'=>$auth,'overdue'=>date('Y-m-d',strtotime('+3 Month')));
		} else { //登录失败
			return array('success'=>0,'errcode'=>1,'errmsg'=>'Wrong password');
		}
	}
	//Auth续期
	public function onrenewAuth () {
		global $isLogin,$auth;
		if (!$isLogin) return array('success'=>0,'errcode'=>1,'errmsg'=>'Auth is not exists');
		$this->sql->query('renewauth','update','auth',array('where'=>array(array('name'=>'auth','type'=>'eq','val'=>$auth)),'update'=>array('overdue'=>date('Y-m-d',strtotime('+3 Month')))));
		return array('success'=>1,'overdue'=>date('Y-m-d',strtotime('+3 Month')));
	}
	//Auth销毁
	public function onremoveAuth () {
		global $isLogin,$uid;
		if (!$isLogin) return array('success'=>0,'errcode'=>1,'errmsg'=>'Auth is not exists');
		$this->sql->query('removeauth','delete','auth',array('where'=>array(array('name'=>'auth','type'=>'eq','val'=>$auth))));
		return array('success'=>1);
	}
	//获取所有用户组
	public function ongetAllGroup () {
		global $isLogin,$uid;
		if (!$isLogin) return array('success'=>0,'errcode'=>1,'errmsg'=>'Auth is not exists');
		$user=$this->sql->GetOne('select','user',array('row'=>'*','where'=>array(array('name'=>'id','type'=>'eq','val'=>$uid))));
		if ($user['isAdmin']!=1) { //检查用户是否为管理员
	 	 	return array('success'=>0,'errcode'=>2,'errmsg'=>'User has not permission to get all user group');
		}
		$this->sql->query('allgroup','select','usergroup',array('row'=>'*'));
		$groups=$this->sql->GetAll('allgroup');
		foreach ($groups as $key=>$val) {
			$groups[$key]['view']=explode('|',trim($groups[$key]['view'],'|'));
			$groups[$key]['control']=explode('|',trim($groups[$key]['control'],'|'));
		}
		return array('success'=>1,'group'=>$groups);
	}
	//获取用户基本信息
	public function ongetMyInfo () {
		global $isLogin,$uid;
		if (!$isLogin) return array('success'=>0,'errcode'=>1,'errmsg'=>'Auth is not exists');
		$user=$this->sql->GetOne('select','user',array('row'=>'*','where'=>array(array('name'=>'id','type'=>'eq','val'=>$uid))));
		$usertype=$user['type'];
		$usergroup=$this->sql->GetOne('select','usergroup',array('row'=>'*','where'=>array(array('name'=>'id','type'=>'eq','val'=>$usertype))));
		$control=explode('|',trim($usergroup['control'],'|'));
		$view=sort(array_merge(explode('|',trim($usergroup['view'],'|')),$control)); //能控制的，必定能查看
		return array('success'=>1,'name'=>$user['name'],'group'=>$usertype,'isAdmin'=>intval($user['isAdmin']),'view'=>$view,'control'=>$control);
	}
	//增加用户
	public function onaddUser () {
		global $isLogin,$uid;
		if (!$isLogin) return array('success'=>0,'errcode'=>1,'errmsg'=>'Auth is not exists');
		$user=$this->sql->GetOne('select','user',array('row'=>'*','where'=>array(array('name'=>'id','type'=>'eq','val'=>$uid))));
		if ($user['isAdmin']!=1) { //检查用户是否为管理员
	 	 	return array('success'=>0,'errcode'=>2,'errmsg'=>'User has not permission to add user');
		}
		$type=getgpc('type','P');
		$name=getgpc('name','P');
		$email=getgpc('email','P');
		$pwd=pwdcode(getgpc('password','P'));
		if (empty($type) || empty($name) || !preg_match('/^[A-Za-z0-9_]+$/',$name) || strlen($name)>20 || !preg_match('/^[_.0-9a-z-]+@([0-9a-z][0-9a-z-]+.)+[a-z]{2,3}$/',$email)) return array('success'=>0,'errcode'=>100,'errmsg'=>'Parameter error'); //格式是否正确
		if ($this->sql->GetNum('usergroup',array('row'=>'*','where'=>array(array('name'=>'id','type'=>'eq','val'=>$type))))<=0) return array('success'=>0,'errcode'=>3,'errmsg'=>'User group not exists'); //用户组是否存在
		if ($this->sql->GetNum('user',array('row'=>'*','where'=>array(array('name'=>'name','type'=>'eq','val'=>$name))))<=0) return array('success'=>0,'errcode'=>4,'errmsg'=>'User already exists'); //用户名是否存在
		if ($this->sql->GetNum('user',array('row'=>'*','where'=>array(array('name'=>'email','type'=>'eq','val'=>$email))))<=0) return array('success'=>0,'errcode'=>5,'errmsg'=>'EMail already exists'); //用户名是否存在
		$this->sql->query('adduser','insert','user',array('insert'=>array('row'=>array('type','name','email'),'val'=>array($type,$name,$email))));
		return array('success'=>1,'id'=>$this->sql->GetLastId());
	}
	//修改用户，未完成
	public function modifyUser () {
	}
	//添加用户组，未完成
	public function onaddGroup () {
		global $isLogin,$uid;
		if (!$isLogin) return array('success'=>0,'errcode'=>1,'errmsg'=>'Auth is not exists');
		$user=$this->sql->GetOne('select','user',array('row'=>'*','where'=>array(array('name'=>'id','type'=>'eq','val'=>$uid))));
		if ($user['isAdmin']!=1) { //检查用户是否为管理员
	 	 	return array('success'=>0,'errcode'=>1,'errmsg'=>'User has not permission to add user group');
		}
		$name=getgpc('name','R');
		$view=getgpc('view','R');
		$control=getgpc('control','R');
	}
}
?>
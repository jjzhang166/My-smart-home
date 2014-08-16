<?php
if (!defined('ROOT')) exit('SmartHome');
/*
 * 模块：用户相关
 * @package Model
*/
class member extends base {
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
		// $pwd=pencode($pwd); 对密码进行加密运算，暂未使用
		if (empty($user) || empty($pwd)) return array('success'=>0,'errcode'=>100,'errmsg'=>'Parameter error');
		$one=$this->sql->GetOne('select','user',array(row=>'*','where'=>array(array('name'=>'user','type'=>'eq','val'=>$user))));
		if ($one===FALSE) return array('success'=>0,'errcode'=>2,'errmsg'=>'User not exists');
		if ($one['password']==$pwd) { //登录成功
			$userid=$one['userid'];
			return array('success'=>1,'auth'=>$userid);
		} else { //登录失败
			return array('success'=>0,'errcode'=>1,'errmsg'=>'Wrong password');
		}
	}
}
?>
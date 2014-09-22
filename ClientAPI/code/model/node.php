<?php
if (!defined('ROOT')) exit('SmartHome');
/*
 * 模块：节点
 * @package Model
*/
class node_model extends base {
	static private $_instance=NULL;
	static public function getInstance () {
		if (!self::$_instance) self::$_instance=new self;
		return self::$_instance;
	}
	public function __construct () {
		parent::init();
	}
	//获取我的节点组
	public function ongetMyGroup () {
		global $isLogin,$uid;
		if (!$isLogin) return array('success'=>0,'errcode'=>1,'errmsg'=>'Auth is not exists');
		$full=intval(getgpc('full','R'));
		$user=$this->sql->GetOne('select','user',array('row'=>'*','where'=>array(array('name'=>'id','type'=>'eq','val'=>$uid))));
		$usertype=$user['type'];
		$usergroup=$this->sql->GetOne('select','usergroup',array('row'=>'*','where'=>array(array('name'=>'id','type'=>'eq','val'=>$usertype))));
		$rawcontrol=explode('|',trim($usergroup['control'],'|'));
		$rawview=array_unique(array_merge(explode('|',trim($usergroup['view'],'|')),$rawcontrol)); //能控制的，必定能查看
		sort($rawview);
		if (in_array('*',$rawview,TRUE)) { //可以查看全部节点
			$this->sql->query('mygroup','select','nodegroup',array('row'=>'*'));
			$group=$this->GetAll('mygroup');
			if ($full===1) {//查询节点组下的节点
				foreach ($group as $one) {
					$id=$one['id'];
					$this->sql->query('getnodes','select','node',array('row'=>'id','where'=>array(array('name'=>'type','type'=>'eq','val'=>$id))));
					//获取当前节点组下的全部节点
					$r=array();
					$nosql=$this->nosql();
					while ($row=$this->sql->GetArray('getnodes')) {
						$tmp=json_decode($nosql->get('node',$row['id']),1);
						$tmp['id']=$row['id'];
						unset($tmp['category']);
						$r[]=$tmp;
					}
					$group[key($group)]['node']=$r;
				} //endforeach
			} //endif
		} else {
			$group=array();
			foreach ($view as $id) {
				$id=intval($id);
				$group[]=$this->sql->GetOne('select','nodegroup',array('row'=>'name','where'=>array(array('name'=>'id','type'=>'eq','val'=>$id))));
				end($group);
				if ($full===1) {//查询节点组下的节点
					$this->sql->query('getnodes','select','node',array('row'=>'id','where'=>array(array('name'=>'type','type'=>'eq','val'=>$id))));
					$r=array();
					$nosql=$this->nosql();
					while ($row=$this->sql->GetArray('getnodes')) {
						$tmp=json_decode($nosql->get('node',$row['id']),1);
						$tmp['id']=$row['id'];
						unset($tmp['category']);
						$r[]=$tmp;
					}
					$group[key($group)]['node']=$r;
				} //endif
			} //endforeach
		}
		$view=$group;
		//可控制的节点组
		$control=array();
		foreach ($rawcontrol as $id) {
			$id=intval($id);
			$control[]=$group[$id];
		}
		return array('success'=>1,'name'=>$nodegroup['name'],'node'=>$r);
	}
	//获取某一节点组的信息
	public function ongetGroupInfo () {
		global $isLogin,$uid;
		if (!$isLogin) return array('success'=>0,'errcode'=>1,'errmsg'=>'Auth is not exists');
		$id=intval(getgpc('id','R'));
		if (empty($id)) return array('success'=>0,'errcode'=>100,'errmsg'=>'Parameter error');
		$user=$this->sql->GetOne('select','user',array('row'=>'*','where'=>array(array('name'=>'id','type'=>'eq','val'=>$uid))));
		$usertype=$user['type'];
		if ($user['isAdmin']!=1) { //检查用户是否有权限查看
			$one=$this->sql->GetOne('select','usergroup',array('row'=>'view,control','where'=>array(array('name'=>'id','type'=>'eq','val'=>$usertype))));
			if (strpos('|'.$id.'|',$one['view']===FALSE) && strpos('|'.$id.'|',$one['control']===FALSE) && $one['view']!='|*|' && $one['control']!='|*|') {
				return array('success'=>0,'errcode'=>3,'errmsg'=>'User has not permission to view');
			}
		}
		//查询节点组信息
		$nodegroup=$this->sql->GetOne('select','nodegroup',array('row'=>'name','where'=>array(array('name'=>'id','type'=>'eq','val'=>$id))));
		if (empty($nodegroup['name'])) return array('success'=>0,'errcode'=>2,'errmsg'=>'Node group not exists');
		//查询节点组下的节点
		$this->sql->query('getnodes','select','node',array('row'=>'id','where'=>array(array('name'=>'type','type'=>'eq','val'=>$id))));
		$r=array();
		$nosql=$this->nosql();
		while ($row=$this->sql->GetArray('getnodes')) {
			$tmp=json_decode($nosql->get('node',$row['id']),1);
			$tmp['id']=$row['id'];
			unset($tmp['category']);
			$r[]=$tmp;
		}
		return array('success'=>1,'name'=>$nodegroup['name'],'node'=>$r);
	}
	//获取所有节点组
	public function ongetAllGroup () {
		global $isLogin,$uid;
		if (!$isLogin) return array('success'=>0,'errcode'=>1,'errmsg'=>'Auth is not exists');
		$user=$this->sql->GetOne('select','user',array('row'=>'type,isAdmin','where'=>array(array('name'=>'id','type'=>'eq','val'=>$uid))));
		$usergroup=$this->sql->GetOne('select','usergroup',array('row'=>'view,control','where'=>array(array('name'=>'id','type'=>'eq','val'=>$user['type']))));
		if ($usergroup['view']!='|*|' && $usergroup['control']!='|*|' && $user['isAdmin']!=1) return array('success'=>0,'errcode'=>2,'errmsg'=>'User has not permission to view');
		$this->sql->query('allgroup','select','nodegroup',array('row'=>'*'));
		$r=array('success'=>1,'group'=>$this->sql->GetAll('allgroup'));
		return $r;
	}
	//获取节点信息
	public function ongetNodeInfo () {
		global $isLogin,$uid;
		if (!$isLogin) return array('success'=>0,'errcode'=>1,'errmsg'=>'Auth is not exists');
		$id=intval(getgpc('id','R'));
		if (empty($id)) return array('success'=>0,'errcode'=>100,'errmsg'=>'Parameter error');
		$nosql=$this->nosql();
		$node=json_decode($nosql->get('node',$id),1);
		if (!is_array($node)) return array('success'=>0,'errcode'=>2,'errmsg'=>'Node not exists');
		$user=$this->sql->GetOne('select','user',array('row'=>'*','where'=>array(array('name'=>'id','type'=>'eq','val'=>$uid))));
		$usertype=$user['type'];
		if ($user['isAdmin']!=1) { //检查用户是否有权限查看
			$one=$this->sql->GetOne('select','usergroup',array('row'=>'view,control','where'=>array(array('name'=>'id','type'=>'eq','val'=>$usertype))));
			if (strpos('|'.$node['category'].'|',$one['view']===FALSE) && strpos('|'.$node['category'].'|',$one['control']===FALSE) && $one['view']!='|*|' && $one['control']!='|*|') {
				return array('success'=>0,'errcode'=>3,'errmsg'=>'User has not permission to view');
			}
		}
		$r=array('success'=>1,'node'=>$node);
		return $r;
	}
	//添加节点，未完成
	public function onaddNode () {
		global $isLogin,$uid;
		if (!$isLogin) return array('success'=>0,'errcode'=>1,'errmsg'=>'Auth is not exists');
		$user=$this->sql->GetOne('select','user',array('row'=>'*','where'=>array(array('name'=>'id','type'=>'eq','val'=>$uid))));
		if ($user['isAdmin']!=1) { //检查用户是否为管理员
	 	 	return array('success'=>0,'errcode'=>2,'errmsg'=>'User has not permission to add node');
		}
		$name=getgpc('name','P');
		$type=getgpc('type','P');
		$hash=getgpc('hash','P');
		if (empty($name) || empty($type) || strlen($hash)!=32) return array('success'=>0,'errcode'=>100,'errmsg'=>'Parameter error');
		//从server获取节点信息
		$control=getClass('control');
		$control->connect(HOME_HOST,HOME_PORT);
		$command=$control->mkCommand('node',array('getinfo',$hash));
		$node=explode(','$control->get($command));
		$nodeinfo=array();
		foreach ($node as $val) {
			$oneinfo=explode('=',$val);
			$nodeinfo[$oneinfo[0]]=$oneinfo[1];
		}
	}
	//添加节点组，未完成
	public function onaddGroup () {
		global $isLogin,$uid;
		if (!$isLogin) return array('success'=>0,'errcode'=>1,'errmsg'=>'Auth is not exists');
		$user=$this->sql->GetOne('select','user',array('row'=>'*','where'=>array(array('name'=>'id','type'=>'eq','val'=>$uid))));
		if ($user['isAdmin']!=1) { //检查用户是否为管理员
	 	 	return array('success'=>0,'errcode'=>2,'errmsg'=>'User has not permission to add node group');
		}
		$name=getgpc('name','P');
		if (empty($name)) return array('success'=>0,'errcode'=>100,'errmsg'=>'Parameter error');
	}
	//控制节点，未完成
	public function oncontrol () {
		global $isLogin,$uid;
		if (!$isLogin) return array('success'=>0,'errcode'=>1,'errmsg'=>'Auth is not exists');
		$id=intval(getgpc('id','R'));
		if (empty($id)) return array('success'=>0,'errcode'=>100,'errmsg'=>'Parameter error');
		$nosql=$this->nosql();
		$node=json_decode($nosql->get('node',$id),1);
		if (!is_array($node)) return array('success'=>0,'errcode'=>2,'errmsg'=>'Node not exists');
		$user=$this->sql->GetOne('select','user',array('row'=>'*','where'=>array(array('name'=>'id','type'=>'eq','val'=>$uid))));
		$usertype=$user['type'];
		if ($user['isAdmin']!=1) { //检查用户是否有权限
			$one=$this->sql->GetOne('select','usergroup',array('row'=>'view,control','where'=>array(array('name'=>'id','type'=>'eq','val'=>$usertype))));
			if (strpos('|'.$node['category'].'|',$one['control']===FALSE) && $one['control']!='|*|') {
				return array('success'=>0,'errcode'=>3,'errmsg'=>'User has not permission to view');
			}
		}
		$command=getgpc('command','R');
		if (empty($command)) return array('success'=>0,'errcode'=>100,'errmsg'=>'Parameter error');
		//$control=getClass('control');
		//$control->connect(HOME_HOST,HOME_PORT);
		//$
		//$r=$control->control(
		// $this->sql->query('command','update','node',array('update'=>array('')));
		// $credis_string=sprintf('exec/credis-php hset %s command %s',$nodeid,$command);
		// exec($credis_string);
	}
}
?>
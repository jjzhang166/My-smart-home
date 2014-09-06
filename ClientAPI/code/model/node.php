<?php
if (!defined('ROOT')) exit('SmartHome');
/*
 * ģ�飺�ڵ�
 * @package Model
*/
class node extends base {
	static private $_instance=NULL;
	static public function getInstance () {
		if (!self::$_instance) self::$_instance=new self;
		return self::$_instance;
	}
	public function __construct () {
		parent::init();
	}
	//��ȡĳһ�ڵ������Ϣ
	public function ongetGroupInfo () {
		global $isLogin,$uid;
		if (!$isLogin) return array('success'=>0,'errcode'=>1,'errmsg'=>'Auth is not exists');
		$id=intval(getgpc('id','R'));
		if (empty($id)) return array('success'=>0,'errcode'=>100,'errmsg'=>'Parameter error');
		$user=$this->sql->GetOne('select','user',array('row'=>'*','where'=>array(array('name'=>'id','type'=>'eq','val'=>$uid))));
		$usertype=$user['type'];
		if ($user['view']!='|*|' && $user['control']!='|*|' && $user['isAdmin']!=1) { //����û��Ƿ���Ȩ�޲鿴
			$num=$this->sql->GetNum('usergroup',array('row'=>'*','where'=>array(array('name'=>'id','type'=>'eq','val'=>$usertype),array('name'=>'view','type'=>'like','val'=>'%|'.$id.'|%'))));
			if ($num==0) {
				$num=$this->sql->GetNum('usergroup',array('row'=>'*','where'=>array(array('name'=>'id','type'=>'eq','val'=>$usertype),array('name'=>'control','type'=>'like','val'=>'%|'.$id.'|%'))));
				if ($num==0) {
					return array('success'=>0,'errcode'=>3,'errmsg'=>'User has not permission to view');
				}
			}
		}
		//��ѯ�ڵ�����Ϣ
		$nodegroup=$this->sql->GetOne('select','nodegroup',array('row'=>'name','where'=>array(array('name'=>'id','type'=>'eq','val'=>$id))));
		if (empty($nodegroup['name'])) return array('success'=>0,'errcode'=>2,'errmsg'=>'Node group not exists');
		//��ѯ�ڵ����µĽڵ�
		$this->sql->query('getnodes','select','node',array('row'=>'id','where'=>array(array('name'=>'type','type'=>'eq','val'=>$id))));
		$r=array();
		while ($row=$this->sql->GetArray('getnodes')) {
			$tmp=json_decode($this->nosql->get('node_'.$row['id']),1);
			$tmp['id']=$row['id'];
		}
		return array('success'=>1,'name'=>$nodegroup['name'],'node'=>$r);
	}
	//��ȡ���нڵ���
	public function ongetAllGroup () {
		global $isLogin,$uid;
		if (!$isLogin) return array('success'=>0,'errcode'=>1,'errmsg'=>'Auth is not exists');
		$user=$this->sql->GetOne('select','user',array('row'=>'*','where'=>array(array('name'=>'id','type'=>'eq','val'=>$uid))));
		if ($user['view']!='|*|' && $user['control']!='|*|' && $user['isAdmin']!=1) return array('success'=>0,'errcode'=>2,'errmsg'=>'User has not permission to view');
		$this->sql->query('allgroup','select','nodegroup',array('row'=>'*'));
		$r=array('success'=>1,'group'=>$this->sql->GetAll('allgroup'));
		return $r;
	}
	//��ȡ�ڵ���Ϣ
	public function ongetNodeInfo () {
		global $isLogin,$uid;
		if (!$isLogin) return array('success'=>0,'errcode'=>1,'errmsg'=>'Auth is not exists');
		$this->sql->query('allgroup','select','nodegroup',array('row'=>'*'));
		$r=array('success'=>1,'group'=>$this->sql->GetAll('allgroup'));
		return $r;
	}
	//���ƽڵ�
	public function oncontrolNode () {
		global $isLogin,$uid;
		$id=getgpc('id','R');
	}
}
?>
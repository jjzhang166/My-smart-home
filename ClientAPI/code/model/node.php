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
		if ($user['isAdmin']!=1) { //����û��Ƿ���Ȩ�޲鿴
			$one=$this->sql->GetOne('select','usergroup',array('row'=>'view,control','where'=>array(array('name'=>'id','type'=>'eq','val'=>$usertype))));
			if (strpos('|'.$id.'|',$one['view']===FALSE) && strpos('|'.$id.'|',$one['control']===FALSE) && $one['view']!='|*|' && $one['control']!='|*|') {
				return array('success'=>0,'errcode'=>3,'errmsg'=>'User has not permission to view');
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
			unset($tmp['category']);
			$r[]=$tmp;
		}
		return array('success'=>1,'name'=>$nodegroup['name'],'node'=>$r);
	}
	//��ȡ���нڵ���
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
	//��ȡ�ڵ���Ϣ
	public function ongetNodeInfo () {
		global $isLogin,$uid;
		if (!$isLogin) return array('success'=>0,'errcode'=>1,'errmsg'=>'Auth is not exists');
		$id=intval(getgpc('id','R'));
		if (empty($id)) return array('success'=>0,'errcode'=>100,'errmsg'=>'Parameter error');
		$node=json_decode($this->nosql->get('node_'.$id),1);
		if (!is_array($node)) return array('success'=>0,'errcode'=>2,'errmsg'=>'Node not exists');
		$user=$this->sql->GetOne('select','user',array('row'=>'*','where'=>array(array('name'=>'id','type'=>'eq','val'=>$uid))));
		$usertype=$user['type'];
		if ($user['isAdmin']!=1) { //����û��Ƿ���Ȩ�޲鿴
			$one=$this->sql->GetOne('select','usergroup',array('row'=>'view,control','where'=>array(array('name'=>'id','type'=>'eq','val'=>$usertype))));
			if (strpos('|'.$node['category'].'|',$one['view']===FALSE) && strpos('|'.$node['category'].'|',$one['control']===FALSE) && $one['view']!='|*|' && $one['control']!='|*|') {
				return array('success'=>0,'errcode'=>3,'errmsg'=>'User has not permission to view');
			}
		}
		$r=array('success'=>1,'node'=>$node);
		return $r;
	}
	//���ƽڵ�
	public function oncontrol () {
		global $isLogin,$uid;
		if (!$isLogin) return array('success'=>0,'errcode'=>1,'errmsg'=>'Auth is not exists');
		$id=intval(getgpc('id','R'));
		if (empty($id)) return array('success'=>0,'errcode'=>100,'errmsg'=>'Parameter error');
		$node=json_decode($this->nosql->get('node_'.$id),1);
		if (!is_array($node)) return array('success'=>0,'errcode'=>2,'errmsg'=>'Node not exists');
		$user=$this->sql->GetOne('select','user',array('row'=>'*','where'=>array(array('name'=>'id','type'=>'eq','val'=>$uid))));
		$usertype=$user['type'];
		if ($user['isAdmin']!=1) { //����û��Ƿ���Ȩ��
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
		redirect(lang('node','command_ok'),'index.php?m=node&a=show');
	}
}
?>
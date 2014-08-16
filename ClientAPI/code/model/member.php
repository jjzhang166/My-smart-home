<?php
if (!defined('ROOT')) exit('SmartHome');
/*
 * ģ�飺�û����
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
	//���е�¼������û���������
	public function onlogin () {
		$user=getgpc('user','P');
		$pwd=getgpc('password','P');
		// $pwd=pencode($pwd); ��������м������㣬��δʹ��
		if (empty($user) || empty($pwd)) return array('success'=>0,'errcode'=>100,'errmsg'=>'Parameter error');
		$one=$this->sql->GetOne('select','user',array(row=>'*','where'=>array(array('name'=>'user','type'=>'eq','val'=>$user))));
		if ($one===FALSE) return array('success'=>0,'errcode'=>2,'errmsg'=>'User not exists');
		if ($one['password']==$pwd) { //��¼�ɹ�
			$userid=$one['userid'];
			return array('success'=>1,'auth'=>$userid);
		} else { //��¼ʧ��
			return array('success'=>0,'errcode'=>1,'errmsg'=>'Wrong password');
		}
	}
}
?>
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
		if (empty($user) || empty($pwd)) exit(json_encode(array('success'=>0,'errcode'=>0,'errmsg'=>'Parameter error')));
		$one=$this->sql->GetOne('select','user',array(row=>'*','where'=>array(array('name'=>'user','type'=>'eq','val'=>$user))));
		if ($one===FALSE) exit(json_encode(array('success'=>0,'errcode'=>2,'errmsg'=>'User not exists')));
		if ($one['password']==$pwd) { //��¼�ɹ�
			$userid=$one['userid'];
			exit(json_encode(array('success'=>1,'auth'=>$userid)));
		} else { //��¼ʧ��
			exit(json_encode(array('success'=>0,'errcode'=>1,'errmsg'=>'Wrong password')));
		}
	}
	//emailuserid����δ����
	public function onemailuserid () {
		return FALSE;
		if (ispost()) {
			$email=getgpc('email','P');
			$userid=md5($email);
			$sql = sprintf("select * from alluser where email='%s'",$email);  
			if(mysql_num_rows($result)>0) {
			die("sorry the email has been used");
			}
			$sql = sprintf("insert into emailmd5 values('%s','%s')",$email,$userid);  
		} else {
			include(TPL.'member_emailuserid.html');
		}
	}
	//ע��
	public function onregister () {
		$name=getgpc('user','P');
		$familyname=getgpc('familyname','P');
		$pwd=getgpc('password','P');
		$email=getgpc('email','P');
		// $pwd=pencode($pwd); ��������м������㣬��δʹ��
		if (empty($name) || empty($pwd) || empty($email)) exit(json_encode(array('success'=>0,'errcode'=>0,'errmsg'=>'Parameter error'))); //��������
		if (!preg_match('/^[A-Za-z0-9_]+$/',$name) && strlen($name)>20) exit(json_encode(array('success'=>0,'errcode'=>1,'errmsg'=>'Format of user is incorrect'))); //�û�����ʽ����
		if (!preg_match('/^[_.0-9a-z-]+@([0-9a-z][0-9a-z-]+.)+[a-z]{2,3}$/',$email)) exit(json_encode(array('success'=>0,'errcode'=>2,'errmsg'=>'Format of EMail is incorrect'))); //EMail��ʽ����
		$num=$this->sql->GetNum('user',array('row'=>'*','where'=>array(array('name'=>'name','type'=>'eq','va;'=>$name))));
		if ($num!=0) exit(json_encode(array('success'=>0,'errcode'=>3,'errmsg'=>'User already exists'))); //�û����Ѵ���
		$num=$this->sql->GetNum('user',array('row'=>'*','where'=>array(array('name'=>'email','type'=>'eq','va;'=>$email))));
		if ($num!=0) exit(json_encode(array('success'=>0,'errcode'=>4,'errmsg'=>'EMail already exists'))); //EMail�Ѵ���
		$this->sql->query('adduser','insert','user',array('insert'=>array('row'=>array('host','hostname','userid','name','password','email','nickname'),'val'=>array('false',$name,md5($email),$familyname,$pwd,$email,$familyname))));
		exit(json_encode(array('success'=>1)));
	}
}
?>
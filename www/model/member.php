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
	public function onlogin () {
		include(TPL.'member_login.html');
	}
	//���е�¼������û���������
	public function oncheck () {
		$name=getgpc('name','P');
		$pwd=getgpc('password','P');
		// $pwd=pencode($pwd); ��������м������㣬��δʹ��
		if (empty($name) || empty($pwd)) redirect(lang('member'.'userpwd_empty'),'-1');
		$one=$this->sql->GetOne('select','alluser',array(row=>'*','where'=>array(array('name'=>'name','type'=>'eq','val'=>$name))));
		if ($one['password']==$pwd) { //��¼�ɹ�
			$userid=$one['userid'];
			setcookie("userid",$userid,time()+24*3600);
			redirect(lang('member','login_success').'<br>Userid:'.$userid,'index.php?m=node&a=show');
		} else { //��¼ʧ��
			redirect(lang('member','login_fail'),'-1');
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
	//ע�ᣬ��δ����
	public function onregister () {
		return FALSE;
		if (ispost()) {
			$sql = sprintf("select * from alluser where email='%s' or name='%s'",$email,$name);  
			if(mysql_num_rows($result)>0){
			die("you have registered , or the email has been used");
			}
			$sql = sprintf("select * from emailmd5 where email='%s' and saltmd5='%s'",$email,$userid);
			$sql = sprintf("insert into alluser values('%s','%s','%s','%s')",$userid,$name,$password,$email);
		} else {
			include(TPL.'member_register.html');
		}
	}
}
?>
<?php
if (!defined('ROOT')) exit('SmartHome');
/*
 * 模块：云端
 * @package Model
*/
class cloud_model extends base {
	static private $_instance=NULL;
	static public function getInstance () {
		if (!self::$_instance) self::$_instance=new self;
		return self::$_instance;
	}
	public function __construct () {
		parent::init();
	}
	//登录云账号
	public function onlogin () {
		$url='http://cloud.smarthome.sylingd.com/api/member/login.json?_r='.time();
		$user=getgpc('user','P');
	}
	//是否上传数据到云端
	private function upload_enable () {
	$nosql=$this->nosql();
	$config=json_decode($nosql->get('cloud','config'),1);
	return $config['upload_to_cloud'];
	}
	//上传记录
	public function onupload () {
		$nosql=$this->nosql();
		$data=$nosql->get('cloud','log');
		//上传数据
		//删除数据
		$nosql->del('cloud','log');
	}
}
?>
<?php
if (!defined('ROOT')) exit('SmartHome');
/*
 * ģ�飺
 * @package Model
*/
class system_model extends base {
	static private $_instance=NULL;
	static public function getInstance () {
		if (!self::$_instance) self::$_instance=new self;
		return self::$_instance;
	}
	public function __construct () {
		parent::init();
	}
	//��ȡϵͳ�汾
	public function ongetVersion () {
		
	}
}
?>
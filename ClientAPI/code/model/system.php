<?php
if (!defined('ROOT')) exit('SmartHome');
/*
 * 模块：
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
	//获取系统版本
	public function ongetVersion () {
		
	}
}
?>
<?php
class control {
	static private $_instance=NULL;
	private $linkID;
	private $host;
	private $port;
	static public function getInstance () {
		if (!self::$_instance) self::$_instance=new self;
		return self::$_instance;
	}
	/*
	 * 初始化
	 * @access public
	*/
	public function __construct () {
	}
	/*
	 * 建立连接
	 * @access public
	 * @param string $host 服务器地址
	 * @param int $port 服务器端口
	*/
	public function connect ($host,$port) {
		if (!preg_match('/^(([01]?[\d]{1,2})|(2[0-4][\d])|(25[0-5]))(\.(([01]?[\d]{1,2})|(2[0-4][\d])|(25[0-5]))){3}$/',$host)) $host=gethostbyname($host); //将非IP转化为IP
		$this->host=$host;
		$this->port=$port;
		if ($host=='127.0.0.1') { //本地连接
			$this->linkID=@socket_create(AF_UNIX,SOCK_DGRAM);
		} else { //远程连接
			$this->linkID=@socket_create(AF_INET,SOCK_DGRAM);
		}
	}
	/*
	 * 发送命令并获取结果
	 * @access public
	 * @param string $command 命令
	 * @return string
	*/
	public function control ($command) {
		if (!@socket_sendto($this->linkID,$command,strlen($command),0,$this->host,$this->port)) {
			$this->DisplayError('Fail to send data');
		}
		$r='';
		if (!@socket_recvfrom($this->linkID,$r,512,0,$this->host,$this->port)) {
			$this->DisplayError('Fail to recvieve data');
		}
		return $r;
	}
	/*
	 * 生成命令
	 * @access public
	 * @param string $type 命令类型，例如node
	 * @param array $data 参数，例如(array('say'=>'ok'),'r')
	 * @return string
	*/
	public function mkCommand ($type,$data) {
	$r=$type;
	for ($i=0;$i<=4;$i++) {
	$r.=' ';
	if (is_array($data[$i])) $r.=join($data[$i],',');
	else $r.='r';
	}
	return $r;
	/*
	 * 报错
	 * @access private
	 * @param string $msg 错误描述
	*/
	private function DisplayError ($msg) {
		$systemmsg=socket_last_error($this->linkID);
		$this->close();
		exit(json_encode(array('success'=>0,'errcode'=>101,'errmsg'=>'Internal Server Error','errtype'=>'socket')));
	}
	/*
	 * 关闭连接
	 * @access private
	*/
	private function close () {
		@socket_close($this->linkID);
		$this->linkID=NULL;
	}
}
?>
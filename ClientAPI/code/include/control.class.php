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
	 * ��ʼ��
	 * @access public
	*/
	public function __construct () {
	}
	/*
	 * ��������
	 * @access public
	 * @param string $host ��������ַ
	 * @param int $port �������˿�
	*/
	public function connect ($host,$port) {
		if (!preg_match('/^(([01]?[\d]{1,2})|(2[0-4][\d])|(25[0-5]))(\.(([01]?[\d]{1,2})|(2[0-4][\d])|(25[0-5]))){3}$/',$host)) $host=gethostbyname($host); //����IPת��ΪIP
		$this->host=$host;
		$this->port=$port;
		if ($host=='127.0.0.1') { //��������
			$this->linkID=@socket_create(AF_UNIX,SOCK_DGRAM);
		} else { //Զ������
			$this->linkID=@socket_create(AF_INET,SOCK_DGRAM);
		}
	}
	/*
	 * ���������ȡ���
	 * @access public
	 * @param string $command ����
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
	 * ��������
	 * @access public
	 * @param string $type �������ͣ�����node
	 * @param array $data ����������(array('say'=>'ok'),'r')
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
	 * ����
	 * @access private
	 * @param string $msg ��������
	*/
	private function DisplayError ($msg) {
		$systemmsg=socket_last_error($this->linkID);
		$this->close();
		exit(json_encode(array('success'=>0,'errcode'=>101,'errmsg'=>'Internal Server Error','errtype'=>'socket')));
	}
	/*
	 * �ر�����
	 * @access private
	*/
	private function close () {
		@socket_close($this->linkID);
		$this->linkID=NULL;
	}
}
?>
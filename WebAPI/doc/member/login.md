[<<����API�б�](http://git.oschina.net/xmeter/My-smart-home/blob/server/WebAPI/doc/list.md)

# WebAPI����¼

***

## ������Ϣ

* ��ַ��`api/member/login.json`

* ����ʽ��POST

* ��ҪAuth����

* ���ظ�ʽ��JSON

## �������

| ���� | ���� | ���� | ʾ�� |
| --- | --- | --- | --- |
| user | �ַ��� | �û��� | admin |
| password | �ַ��� | ���룬��ʱ���Ĵ��䣬���ڿ��ܻ���� | 123456

## ���ز���

| ���� | ���� | ���� | ʾ�� |
| --- | --- | --- | --- |
| success | ���� | �Ƿ�ɹ���0Ϊʧ�� | 1 |
| auth | �ַ��� | ��Ȩ�ַ���������󲿷�APIʱ��Ҫ���ϣ�ͳһΪСд�����ɹ�ʱ���� | 21232f297a57a5a743894a0e4a801fc3 |
| errcode | ���� | �����룬�μ����� | 0 |
| errmsg | �ַ��� | ������ʾ��ΪӢ�ģ���ֱ����� | Wrong password |

## ����ʾ��

	curl -X POST http://server.smarthome.sylingd.com/api/member/login -d 'user=admin&password=123456'

����ɹ���������Ϣ���£�

	{
		"success": 1,
		"auth": "21232f297a57a5a743894a0e4a801fc3"
	}

���ʧ�ܣ�������Ϣ���£�

	{
		"success": 0,
		"errcode": 0,
		"errmsg": "Wrong password"
	}

## ע������

��

## ������������

| ������ | ���� |
| --- | --- |
| 0 | ������� |
| 1 | �û������� |
| 2 | �û�����ֹ��¼ |
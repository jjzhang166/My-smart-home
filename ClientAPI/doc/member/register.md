[<<����API�б�](../list.md)

# WebAPI��ע��

***

## ������Ϣ

* ��ַ��`api/member/register.json`

* ����ʽ��POST

* ��ҪAuth����

* ���ظ�ʽ��JSON

## �������

| ���� | ���� | ���� | ʾ�� |
| --- | --- | --- | --- |
| user | �ַ��� | �û��������������֡���ĸ���»��� | admin |
| familyname | �ַ��� | �ǳ� | Jack |
| email | �ַ��� | ���� | example@example.com |
| password | �ַ��� | ���룬��ʱ���Ĵ��䣬���ڿ��ܻ���� | 123456 |

## ���ز���

| ���� | ���� | ���� | ʾ�� |
| --- | --- | --- | --- |
| success | ���� | �Ƿ�ɹ���0Ϊʧ�� | 1 |
| errcode | ���� | �����룬��ʧ��ʱ���ڡ��μ����� | 0 |
| errmsg | �ַ��� | ������ʾ����ʧ��ʱ���ڣ�ΪӢ�ģ���ֱ����� | Format of user is incorrect |

## ����ʾ��

	curl -X POST http://server.smarthome.sylingd.com/api/member/register.json -d 'user=admin&familyname=Jack&email=example@example.com&password=123456'

����ɹ���������Ϣ���£�

	{
		"success": 1
	}

���ʧ�ܣ�������Ϣ���£�

	{
		"success": 0,
		"errcode": 0,
		"errmsg": "Format of user is incorrect"
	}

## ע������

��

## ����������

| ������ | ���� |
| --- | --- |
| 0 | ����������� |
| 1 | �û�����ʽ���� |
| 2 | EMail��ʽ���� |
| 3 | �û����Ѵ��� |
| 4 | EMail�Ѵ��� |
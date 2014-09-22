[<<����API�б�](../list.md)

# WebAPI������û�

***

## ������Ϣ

* ��ַ��`api/member/addUser.json`

* ����ʽ��POST/GET

* ��ҪAuth����

* ��Ҫ����ԱȨ�ޣ���

* ���ظ�ʽ��JSON

* ����ȫ�ַ��أ���

## �������

| ���� | ���� | ���� | ʾ�� |
| --- | --- | --- | --- |
| auth | �ַ��� | ��Ȩ�ַ�����ͨ����¼API��ȡ | 21232f297a57a5a743894a0e4a801fc3 |
| type | ���� | �û���ID | 1 |
| user | �ַ��� | �û�����20�ֽ����ڣ���֧��Ӣ����ĸ�����ֺ��»��ߣ�_�� | admin |
| email | �ַ��� | EMail | example@example.com |
| password | �ַ��� | ���룬��ʱ���Ĵ��䣬���ڿ��ܻ���� | 123456 |

## ���ز���

| ���� | ���� | ���� | ʾ�� |
| --- | --- | --- | --- |
| id | ���� | �û�ID�����ɹ�ʱ���� | 1 |

## ����ʾ��

	curl -X POST http://client.smarthome.sylingd.com/api/member/addUser.json -d 'auth=21232f297a57a5a743894a0e4a801fc3&user=admin&email=example@example.com&password=123456'

����ɹ���������Ϣ���£�

	{
		"success": 1,
		"id": 1
	}

���ʧ�ܣ�������Ϣ���£�

	{
		"success": 0,
		"errcode": 1,
		"errmsg": "Auth is not exists"
	}

## ע������

* ��

## ����������

| ������ | ���� |
| --- | --- |
| 1 | Auth�����ڻ��ѹ��� |
| 2 | ��ǰAuth��Ӧ���û�û��Ȩ�� |
| 3 | �û��鲻���� |
| 4 | �û����Ѵ��� |
| 5 | EMail�Ѵ��� |
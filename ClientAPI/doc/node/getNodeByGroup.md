[<<����API�б�](../list.md)

# WebAPI����ȡĳһ�ڵ����µ����нڵ�

***

## ������Ϣ

* ��ַ��`api/node/getNodeByGroup.json`

* ����ʽ��POST/GET

* ��ҪAuth����

* ���ظ�ʽ��JSON

* ����ȫ�ַ��أ���

## �������

| ���� | ���� | ���� | ʾ�� |
| --- | --- | --- | --- |
| auth | �ַ��� | ��Ȩ�ַ�����ͨ����¼API��ȡ | 21232f297a57a5a743894a0e4a801fc3 |
| id | ���� | �ڵ����ID | 1 |

## ���ز���

| ���� | ���� | ���� | ʾ�� |
| --- | --- | --- | --- |
| node | ���� | �ڵ����µ����нڵ� | [{"id":1,"name":"Light-Kitchen","category":1,"value":"on"},{"id":2,"name":"TV-bedroom","category":2,"value":"on"}] |
| errcode | ���� | �����룬�μ�������ʧ��ʱ���� | 0 |

## ����ʾ��

	curl -X POST http://client.smarthome.sylingd.com/api/node/getNodeByGroup.json -d 'auth=21232f297a57a5a743894a0e4a801fc3&id=1'

����ɹ���������Ϣ���£�

	{
		"success": 1,
		"node": [
			{
				"id": 1,
				"name": "Light-Kitchen",
				"category": 1,
				"value": "on"
			},
			{
				"id": 2,
				"name": "TV-bedroom",
				"category": 2,
				"value": "on"
			}
		]
	}

���ʧ�ܣ�������Ϣ���£�

	{
		"success": 0,
		"errcode": 1,
		"errmsg": "Auth is not exists"
	}

## ע������

node����Ϊ������

## ����������

| ������ | ���� |
| --- | --- |
| 1 | Auth�����ڻ��ѹ��� |
| 2 | �û�û�в鿴Ȩ�� |
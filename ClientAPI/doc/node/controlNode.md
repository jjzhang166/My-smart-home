[<<����API�б�](../list.md)

# WebAPI�����ƽڵ�

***

## ������Ϣ

* ��ַ��`api/node/controlNode.json`

* ����ʽ��POST/GET

* ��ҪAuth����

* ��Ҫ����ԱȨ�ޣ���

* ���ظ�ʽ��JSON

* ����ȫ�ַ��أ���

## �������

| ���� | ���� | ���� | ʾ�� |
| --- | --- | --- | --- |
| auth | �ַ��� | ��Ȩ�ַ�����ͨ����¼API��ȡ | 21232f297a57a5a743894a0e4a801fc3 |
| id | ���� | �ڵ��ID | 1 |

## ���ز���

| ���� | ���� | ���� | ʾ�� |
| --- | --- | --- | --- |
| node | ���� | �ڵ�״̬ | 0 |
| errcode | ���� | �����룬�μ�������ʧ��ʱ���� | 0 |

## ����ʾ��

	curl -X POST http://client.smarthome.sylingd.com/api/node/controlNode.json -d 'auth=21232f297a57a5a743894a0e4a801fc3&id=1'

����ɹ���������Ϣ���£�

	{
		"success": 1,
		"node": [
			{
				"id": 1,
				"name": "Light-Kitchen",
				"category": 1,
				"state": "on",
				"attach": {
					"brightness": 80
				}
			},
			{
				"id": 2,
				"name": "TV-bedroom",
				"category": 2,
				"state": "on",
				"attach": {}
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

* node����Ϊ������

## ����������

| ������ | ���� |
| --- | --- |
| 1 | Auth�����ڻ��ѹ��� |
| 2 | �ڵ��鲻���� |
| 3 | �û�û�в鿴Ȩ�� |
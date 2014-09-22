[<<����API�б�](../list.md)

# WebAPI����ȡ�����û���

***

## ������Ϣ

* ��ַ��`api/member/getAllGroup.json`

* ����ʽ��POST/GET

* ��ҪAuth����

* ��Ҫ����ԱȨ�ޣ���

* ���ظ�ʽ��JSON

* ����ȫ�ַ��أ���

## �������

| ���� | ���� | ���� | ʾ�� |
| --- | --- | --- | --- |
| auth | �ַ��� | ��Ȩ�ַ�����ͨ����¼API��ȡ | 21232f297a57a5a743894a0e4a801fc3 |

## ���ز���

| ���� | ���� | ���� | ʾ�� |
| --- | --- | --- | --- |
| group | ���� | �����û��� | [{"id":1,"name":"Administrator","view":["*"],"control":["*"]}] |
| group[][id] | ���� | �û���ID | 1 |
| group[][name] | �ַ��� | �û������� | Administrator |
| group[][view] | ���� | �ɲ鿴�Ľڵ��飨�����ȫ������ֻ��һ����*��Ԫ�أ����ɿ��Ƶģ��ض��ɲ鿴 | ["1","2","3"] |
| group[][control] | ���� | �ɿ��ƵĽڵ��飨�����ȫ������ֻ��һ����*��Ԫ�أ� | ["1","2"] |

## ����ʾ��

	curl -X POST http://client.smarthome.sylingd.com/api/member/getAllGroup.json -d 'auth=21232f297a57a5a743894a0e4a801fc3'

����ɹ���������Ϣ���£�

	{
		"success": 1,
		"group": [
			{
				"id": 1,
				"name": "Administrator",
				"view": ["*"],
				"control": ["*"]
			},
			{
				"id": 2,
				"name": "IT",
				"view": ["1","2","3"],
				"control": ["1","2"]
			},
			{
				"id": 2,
				"name": "Office",
				"view": ["1","2"],
				"control": ["1","2","3"]
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

* ��

## ����������

| ������ | ���� |
| --- | --- |
| 1 | Auth�����ڻ��ѹ��� |
| 2 | �û�û��Ȩ�޵��ô�API |
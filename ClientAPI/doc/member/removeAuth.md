[<<����API�б�](../list.md)

# WebAPI���Ƴ�Auth

***

## ������Ϣ

* ��ַ��`api/member/removeAuth.json`

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

�����ⷵ�ز���

## ����ʾ��

	curl -X POST http://client.smarthome.sylingd.com/api/member/removeAuth.json -d 'auth=21232f297a57a5a743894a0e4a801fc3'

����ɹ���������Ϣ���£�

	{
		"success": 1
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
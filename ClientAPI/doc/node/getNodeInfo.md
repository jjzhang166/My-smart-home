[<<����API�б�](../list.md)

# WebAPI����ȡ�ڵ���Ϣ

***

## ������Ϣ

* ��ַ��`api/node/getNodeInfo.json`

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
| node | ���� | �ڵ����Ϣ | [{"id":1,"name":"Light-Kitchen","category":1,"state":"on","attach":{"brightness":80}},{"id":2,"name":"TV-bedroom","category":2,"state":"on","attach":{}}] |
| node[id] | ���� | �ڵ�ID | 1 |
| node[name] | �ַ��� | �ڵ����� | 1 |
| node[category] | ���� | �ڵ����ͣ��μ�[���ݿ���ڵ�](http://git.oschina.net/xmeter/My-smart-home/wikis/%E6%95%B0%E6%8D%AE%E5%BA%93%E4%B8%8E%E8%8A%82%E7%82%B9) | 1 |
| node[state] | �ַ��� | ��ǰ״̬���μ�[���ݿ���ڵ�](http://git.oschina.net/xmeter/My-smart-home/wikis/%E6%95%B0%E6%8D%AE%E5%BA%93%E4%B8%8E%E8%8A%82%E7%82%B9) | on |
| node[attach] | ���� | �������ԣ��μ�[���ݿ���ڵ�](http://git.oschina.net/xmeter/My-smart-home/wikis/%E6%95%B0%E6%8D%AE%E5%BA%93%E4%B8%8E%E8%8A%82%E7%82%B9) | {"brightness":80} |
| errcode | ���� | �����룬�μ�������ʧ��ʱ���� | 0 |

## ����ʾ��

	curl -X POST http://client.smarthome.sylingd.com/api/node/getGroupInfo.json -d 'auth=21232f297a57a5a743894a0e4a801fc3&id=1'

����ɹ���������Ϣ���£�

	{
		"success": 1,
		"node": {
			"id": 1,
			"name": "Light-Kitchen",
			"category": 1,
			"state": "on",
			"attach": {
				"brightness": 80
			}
		}
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
| 2 | �ڵ��鲻���� |
| 3 | �û�û�в鿴Ȩ�� |
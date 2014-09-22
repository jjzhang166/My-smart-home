[<<返回API列表](../list.md)

# WebAPI：获取我的节点组

***

## 基本信息

* 地址：`api/node/getMyGroup.json`

* 请求方式：POST/GET

* 需要Auth：是

* 需要管理员权限：否

* 返回格式：JSON

* 包含全局返回：是

## 请求参数

| 名称 | 类型 | 描述 | 示例 |
| --- | --- | --- | --- |
| auth | 字符串 | 授权字符串，通过登录API获取 | 21232f297a57a5a743894a0e4a801fc3 |

## 返回参数

| 名称 | 类型 | 描述 | 示例 |
| --- | --- | --- | --- |
| view | 数组 | 可查看的节点组 | [{"id":1,"name":"Light-Kitchen","category":1,"state":"on","attach":{"brightness":80}},{"id":2,"name":"TV-bedroom","category":2,"state":"on","attach":{}}] |
| view[id] | 数字 | 节点ID | 1 |
| view[name] | 字符串 | 节点名称 | 1 |
| view[category] | 数字 | 节点类型，参见[数据库与节点](http://git.oschina.net/xmeter/My-smart-home/wikis/%E6%95%B0%E6%8D%AE%E5%BA%93%E4%B8%8E%E8%8A%82%E7%82%B9) | 1 |
| view[state] | 字符串 | 当前状态，参见[数据库与节点](http://git.oschina.net/xmeter/My-smart-home/wikis/%E6%95%B0%E6%8D%AE%E5%BA%93%E4%B8%8E%E8%8A%82%E7%82%B9) | on |
| view[attach] | 数组 | 附加属性，参见[数据库与节点](http://git.oschina.net/xmeter/My-smart-home/wikis/%E6%95%B0%E6%8D%AE%E5%BA%93%E4%B8%8E%E8%8A%82%E7%82%B9) | {"brightness":80} |
| control | 数组 | 可控制的节点组，结构同view | [{"id":1,"name":"Light-Kitchen","category":1,"state":"on","attach":{"brightness":80}},{"id":2,"name":"TV-bedroom","category":2,"state":"on","attach":{}}] |

## 请求示例

	curl -X POST http://client.smarthome.sylingd.com/api/node/getMyGroup.json -d 'auth=21232f297a57a5a743894a0e4a801fc3'

如果成功，返回信息如下：

	{
		"success": 1,
		"view": {
			"id": 1,
			"name": "Light-Kitchen",
			"category": 1,
			"state": "on",
			"attach": {
				"brightness": 80
			}
		},
		"control": {
			"id": 1,
			"name": "Light-Kitchen",
			"category": 1,
			"state": "on",
			"attach": {
				"brightness": 80
			}
		}
	}

如果失败，返回信息如下：

	{
		"success": 0,
		"errcode": 1,
		"errmsg": "Auth is not exists"
	}

## 注意事项

* 无

## 附表：错误码

| 错误码 | 描述 |
| --- | --- |
| 1 | Auth不存在或已过期 |
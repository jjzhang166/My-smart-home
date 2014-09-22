[<<返回API列表](../list.md)

# WebAPI：控制节点

***

## 基本信息

* 地址：`api/node/controlNode.json`

* 请求方式：POST/GET

* 需要Auth：是

* 需要管理员权限：否

* 返回格式：JSON

* 包含全局返回：是

## 请求参数

| 名称 | 类型 | 描述 | 示例 |
| --- | --- | --- | --- |
| auth | 字符串 | 授权字符串，通过登录API获取 | 21232f297a57a5a743894a0e4a801fc3 |
| id | 数字 | 节点的ID | 1 |

## 返回参数

| 名称 | 类型 | 描述 | 示例 |
| --- | --- | --- | --- |
| node | 数组 | 节点状态 | 0 |
| errcode | 数字 | 错误码，参见附表，仅失败时存在 | 0 |

## 请求示例

	curl -X POST http://client.smarthome.sylingd.com/api/node/controlNode.json -d 'auth=21232f297a57a5a743894a0e4a801fc3&id=1'

如果成功，返回信息如下：

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

如果失败，返回信息如下：

	{
		"success": 0,
		"errcode": 1,
		"errmsg": "Auth is not exists"
	}

## 注意事项

* node可能为空数组

## 附表：错误码

| 错误码 | 描述 |
| --- | --- |
| 1 | Auth不存在或已过期 |
| 2 | 节点组不存在 |
| 3 | 用户没有查看权限 |
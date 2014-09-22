[<<返回API列表](../list.md)

# WebAPI：获取所有用户组

***

## 基本信息

* 地址：`api/member/getAllGroup.json`

* 请求方式：POST/GET

* 需要Auth：是

* 需要管理员权限：是

* 返回格式：JSON

* 包含全局返回：是

## 请求参数

| 名称 | 类型 | 描述 | 示例 |
| --- | --- | --- | --- |
| auth | 字符串 | 授权字符串，通过登录API获取 | 21232f297a57a5a743894a0e4a801fc3 |

## 返回参数

| 名称 | 类型 | 描述 | 示例 |
| --- | --- | --- | --- |
| group | 数组 | 所有用户组 | [{"id":1,"name":"Administrator","view":["*"],"control":["*"]}] |
| group[][id] | 数字 | 用户组ID | 1 |
| group[][name] | 字符串 | 用户组名称 | Administrator |
| group[][view] | 数组 | 可查看的节点组（如果是全部，则只有一个“*”元素），可控制的，必定可查看 | ["1","2","3"] |
| group[][control] | 数组 | 可控制的节点组（如果是全部，则只有一个“*”元素） | ["1","2"] |

## 请求示例

	curl -X POST http://client.smarthome.sylingd.com/api/member/getAllGroup.json -d 'auth=21232f297a57a5a743894a0e4a801fc3'

如果成功，返回信息如下：

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
| 2 | 用户没有权限调用此API |
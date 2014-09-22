[<<返回API列表](../list.md)

# WebAPI：添加用户

***

## 基本信息

* 地址：`api/member/addUser.json`

* 请求方式：POST/GET

* 需要Auth：是

* 需要管理员权限：是

* 返回格式：JSON

* 包含全局返回：是

## 请求参数

| 名称 | 类型 | 描述 | 示例 |
| --- | --- | --- | --- |
| auth | 字符串 | 授权字符串，通过登录API获取 | 21232f297a57a5a743894a0e4a801fc3 |
| type | 数字 | 用户组ID | 1 |
| user | 字符串 | 用户名，20字节以内，仅支持英文字母、数字和下划线（_） | admin |
| email | 字符串 | EMail | example@example.com |
| password | 字符串 | 密码，暂时明文传输，后期可能会加密 | 123456 |

## 返回参数

| 名称 | 类型 | 描述 | 示例 |
| --- | --- | --- | --- |
| id | 数字 | 用户ID，仅成功时存在 | 1 |

## 请求示例

	curl -X POST http://client.smarthome.sylingd.com/api/member/addUser.json -d 'auth=21232f297a57a5a743894a0e4a801fc3&user=admin&email=example@example.com&password=123456'

如果成功，返回信息如下：

	{
		"success": 1,
		"id": 1
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
| 2 | 当前Auth对应的用户没有权限 |
| 3 | 用户组不存在 |
| 4 | 用户名已存在 |
| 5 | EMail已存在 |
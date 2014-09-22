[<<返回API列表](../list.md)

# WebAPI：移除Auth

***

## 基本信息

* 地址：`api/member/removeAuth.json`

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

无特殊返回参数

## 请求示例

	curl -X POST http://client.smarthome.sylingd.com/api/member/removeAuth.json -d 'auth=21232f297a57a5a743894a0e4a801fc3'

如果成功，返回信息如下：

	{
		"success": 1
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
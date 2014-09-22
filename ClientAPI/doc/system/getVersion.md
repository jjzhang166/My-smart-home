[<<返回API列表](../list.md)

# WebAPI：获取系统版本

***

## 基本信息

* 地址：`api/system/getVersion.json`

* 请求方式：POST/GET

* 需要Auth：否

* 需要管理员权限：否

* 返回格式：JSON

* 包含全局返回：是

## 请求参数

| 名称 | 类型 | 描述 | 示例 |
| --- | --- | --- | --- |
|  |  |  |  |

## 返回参数

| 名称 | 类型 | 描述 | 示例 |
| --- | --- | --- | --- |
|  |  |  |  |

## 请求示例

	curl -X GET http://client.smarthome.sylingd.com/api/system/getVersion.json

如果成功，返回信息如下：

	{
		"success": 1,
		
	}

如果失败，返回信息如下：

	{
		"success": 0,
		"errcode": 1,
		"errmsg": ""
	}

## 注意事项

* 无
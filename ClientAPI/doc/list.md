# API列表

***

## 总则

* API命名遵循[小驼峰式命名法](http://zh.wikipedia.org/wiki/%E9%A7%9D%E5%B3%B0%E5%BC%8F%E5%A4%A7%E5%B0%8F%E5%AF%AB)

* 使用JavaScript调用API时，为了防止缓存，可加上随机参数，此处定为r，例如`api/member/login.json?_r=12345821`，此参数不会被使用

## 全局返回

### 如不特殊说明，则所有API都会返回此处的参数

| 名称 | 类型 | 描述 | 示例 |
| --- | --- | --- | --- |
| success | 数字 | 是否成功，0为失败 | 1 |
| errcode | 数字 | 错误码，参见附表，仅失败时存在 | 0 |
| errmsg | 字符串 | 错误提示，为英文，可直接输出，仅失败时存在 | API Not Found |

### 附表：错误码说明

| 错误码 | 描述 |
| --- | --- |
| 100 | 请求参数错误 |
| 101 | 服务器内部错误 |
| 102 | 未知错误 |
| 103 | 操作被禁止 |
| 104 | 请求的API不存在 |

## 系统相关（system）

* 获取版本信息（开发中）：[getVersion](system/getVersion.md)

## 用户相关（member）

* 登录：[login](member/login.md)

* 获取“我的信息”：[getMyInfo](member/getMyInfo.md)

* 获取所有用户组：[getAllGroup](member/getAllGroup.md)

* 移除Auth：[removeAuth](member/removeAuth.md)

* 续期Auth：[renewAuth](member/renewAuth.md)

* 添加用户（开发中）：[addUser](member/addUser.md)

## 节点相关（node）

* 获取所有节点组：[getAllGroup](node/getAllGroup.md)

* 获取某一节点组信息：[getGroupInfo](node/getGroupInfo.md)

* 获取某一节点信息：[getNodeInfo](node/getNodeInfo.md)

* 获取我的节点组：[getMyGroup](node/getMyGroup.md)

* 控制节点（开发中）：[controlNode](node/controlNode.md)
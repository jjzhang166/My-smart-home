// Beego (http://beego.me/)

// @description beego is an open-source, high-performance web framework for the Go programming language.

// @link        http://github.com/astaxie/beego for the canonical source repository

// @license     http://github.com/astaxie/beego/blob/master/LICENSE

// @authors     astaxie

//  modified by yongming.li

package main

import (
  "restful-server/controllers"

  "github.com/astaxie/beego"
)

//		Objects

//	URL					HTTP Verb				Functionality
//	/object				POST					Creating Objects
//	/object/<objectId>	GET						Retrieving Objects
//	/object/<objectId>	PUT						Updating Objects
//	/object				GET						Queries
//	/object/<objectId>	DELETE					Deleting Objects

//func main() {
//	beego.RESTRouter("/object", &controllers.ObjectController{})
//	beego.Run()
//}

func main() {
  //myinit()
  //beego.Router("/user/?username", &MainController{})
  beego.Router("/user/", &controllers.MainController{})
  beego.Router("/user/node/:username", &controllers.NodeController{})
  //beego.Router("/", &MainController{})
  beego.Run()
}

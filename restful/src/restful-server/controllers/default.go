// auther:  yongming.li
package controllers

import (
  "encoding/json"
  "fmt"
  "net/http"

  "restful-server/models"

  "github.com/astaxie/beego"
)

/////////////////////////////////////////////////////////////////////////
type Server struct {
  ServerName string
  ServerIP   string
}

type Serverslice struct {
  Servers []Server
}

type MainController struct {
  beego.Controller
}

// added by yongming.li post demo just for test
func (this *MainController) Post() {
  var s Serverslice
  s.Servers = append(s.Servers, Server{ServerName: "Shanghai_VPN", ServerIP: "127.0.0.1"})
  s.Servers = append(s.Servers, Server{ServerName: "Beijing_VPN", ServerIP: "127.0.0.2"})
  b, err := json.Marshal(s)
  if err != nil {
    fmt.Println("json err:", err)
    this.Ctx.ResponseWriter.WriteHeader(http.StatusInternalServerError)
    return
  }
  //this.Ctx.WriteString("lizi")
  this.Ctx.WriteString(string(b))
  return
}

func (this *MainController) Get() {

  //this.Ctx.WriteString("your name is : "+this.Ctx.Input.Param(":username"))
  //return

  //this.Ctx.WriteString("lizi")
  //this.Ctx.WriteString(string(b))
  // return

  //userid      string
  //name       string
  //password    string
  //email       string

  // 插入数据
  //stmt, err := db.Prepare("INSERT alluser SET userid=?,name=?,password=?,email=?")
  //checkErr(err)
  //res, err := stmt.Exec("astaxie111", "jfksdjfkldsjkl", "2012-12-09","shit")
  //checkErr(err)
  //id, err := res.LastInsertId()
  //checkErr(err)
  //fmt.Println(id)
  // 更新数据
  //stmt, err = db.Prepare("update userinfo set username=? where uid=?")
  //checkErr(err)
  //res, err = stmt.Exec("astaxieupdate", id)
  //checkErr(err)
  //affect, err := res.RowsAffected()
  //checkErr(err)
  //fmt.Println(affect)
  // 查询数据
  //(userid VARCHAR(50) UNIQUE,name VARCHAR(50)  ,password VARCHAR(50),email VARCHAR(50) , PRIMARY KEY (`name`))",$con);

  u := models.GetAllUserInfo()
  b, err := json.Marshal(map[string][]models.Userinfo{"Userinfos": u})
  if err != nil {
    fmt.Println("json err:", err)
    this.Ctx.ResponseWriter.WriteHeader(http.StatusInternalServerError)
    return
  }
  this.Ctx.WriteString(string(b))

  // 删除数据
  //stmt, err = db.Prepare("delete from userinfo where uid=?")
  //checkErr(err)
  //res, err = stmt.Exec(id)
  //checkErr(err)
  //affect, err = res.RowsAffected()
  //checkErr(err)
  //fmt.Println(affect)
}

type NodeController struct {
  beego.Controller
}

func (this *NodeController) Get() {
  name := this.Ctx.Input.Param(":username")
  fmt.Println("name:", name)
  userid := models.GetUseridByName(name)
  fmt.Println("userid:", userid)
  // 查询数据
  node := models.GetNodeInfo(userid)
  b, err := json.Marshal(map[string][]models.Nodeinfo{"Nodeinfos": node})
  if err != nil {
    fmt.Println("json err:", err)
    this.Ctx.ResponseWriter.WriteHeader(http.StatusInternalServerError)
    return
  }
  this.Ctx.WriteString(string(b))
}

func checkErr(err error) {
  if err != nil {
    panic(err)
  }
}

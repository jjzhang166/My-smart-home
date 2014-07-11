// auther:  yongming.li
package controllers

import (
  "database/sql"
  "encoding/json"
  "fmt"

  "github.com/astaxie/beego"
  "github.com/astaxie/beego/orm"
  _ "github.com/go-sql-driver/mysql"
)

////////////////////////////////////////////////////////////////////////
type User struct {
  userid   string
  name     string
  password string
  email    string
}

func myinit() {
  // 需要在init中注册定义的model
  orm.RegisterModel(new(User))
  orm.RegisterDriver("mysql", orm.DR_MySQL)
  orm.RegisterDataBase("mynode", "mysql", "root:123456@/mynode?charset=utf8", 30)
}

// init mysql driver
var DefaultDB *sql.DB = nil

func InitMysqlDriver() {
  var err error
  DefaultDB, err = sql.Open("mysql", "root:123456@/mynode?charset=utf8")
  checkErr(err)
}

// close the mysql driver when progress exited
func CloseMysqlDriver() {
  if DefaultDB != nil {
    DefaultDB.Close()
  }
}

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
  }
  b = b
  //this.Ctx.WriteString("lizi")
  this.Ctx.WriteString(string(b))
  return
}

type Userinfo struct {
  UserName  string
  UserID    string
  UserEmail string
}
type Userinfoslice struct {
  Userinfos []Userinfo
}

func (this *MainController) Get() {

  //this.Ctx.WriteString("your name is : "+this.Ctx.Input.Param(":username"))
  //return
  var u Userinfoslice

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
  rows, err := DefaultDB.Query("SELECT userid, name, email FROM alluser")
  checkErr(err)
  for rows.Next() {
    var userid string
    var name string
    var email string
    err = rows.Scan(&userid, &name, &email)
    checkErr(err)
    //fmt.Println(userid)
    //fmt.Println(name)
    //fmt.Println(password)
    //fmt.Println(email)
    u.Userinfos = append(u.Userinfos, Userinfo{UserName: name, UserID: userid, UserEmail: email})
  }
  b, err := json.Marshal(u)
  if err != nil {
    fmt.Println("json err:", err)
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

type Nodeinfo struct {
  NodeID string
}

type Nodeinfoslice struct {
  Nodeinfos []Nodeinfo
}

type NodeController struct {
  beego.Controller
}

func (this *NodeController) Get() {

  var (
    node   Nodeinfoslice
    name   string
    userid string
    strSql string
  )

  name = this.Ctx.Input.Param(":username")
  strSql = "name is " + name
  fmt.Println(strSql)
  strSql = "SELECT userid FROM alluser WHERE name=" + "'" + name + "'"
  rows, err := DefaultDB.Query(strSql)
  fmt.Println(strSql)
  checkErr(err)
  for rows.Next() {
    err = rows.Scan(&userid)
    checkErr(err)
    fmt.Println("userid is " + userid)
    break
  }
  // 查询数据
  strSql = "SELECT nodeid FROM node where userid =" + "'" + userid + "'"
  fmt.Println(strSql)
  rows, err = DefaultDB.Query(strSql)
  checkErr(err)
  for rows.Next() {
    var nodeid string
    err = rows.Scan(&nodeid)
    checkErr(err)
    node.Nodeinfos = append(node.Nodeinfos, Nodeinfo{NodeID: nodeid})
  }
  b, err := json.Marshal(node)
  if err != nil {
    fmt.Println("json err:", err)
  }
  this.Ctx.WriteString(string(b))
}
func checkErr(err error) {
  if err != nil {
    panic(err)
  }
}

package models

import (
  "database/sql"
  "fmt"

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

type Userinfo struct {
  UserName  string
  UserID    string
  UserEmail string
}

func InitORM() {
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

func checkErr(err error) {
  if err != nil {
    panic(err)
  }
}

// userinfo
func GetAllUserInfo() (infos []Userinfo) {
  rows, err := DefaultDB.Query("SELECT `userid`,`name`,`email` FROM `alluser`")
  checkErr(err)
  // close to free sql connection
  defer rows.Close()
  for rows.Next() {
    var userid, name, email string
    err = rows.Scan(&userid, &name, &email)
    checkErr(err)
    //fmt.Println("userid: %s, name: %s, email: %s\n", userid, name, email)
    infos = append(infos, Userinfo{UserName: name, UserID: userid, UserEmail: email})
  }
  return
}

// userid
func GetUseridByName(name string) (userid string) {
  strSql := fmt.Sprintf("SELECT `userid` FROM `alluser` WHERE `name`='%s' limit 1", name)
  err := DefaultDB.QueryRow(strSql).Scan(&userid)
  fmt.Println(strSql)
  checkErr(err)
  return
}

/////////////////////////////////////////////////////////////////////
type Nodeinfo struct {
  NodeID string
}

// nodeinfo
func GetNodeInfo(userid string) (infos []Nodeinfo) {
  strSql := fmt.Sprintf("SELECT `nodeid` FROM `node` where `userid`='%s'", userid)
  fmt.Println(strSql)
  rows, err := DefaultDB.Query(strSql)
  checkErr(err)
  // close to free sql connection
  defer rows.Close()
  for rows.Next() {
    var nodeid string
    err = rows.Scan(&nodeid)
    checkErr(err)
    infos = append(infos, Nodeinfo{nodeid})
  }
  return
}

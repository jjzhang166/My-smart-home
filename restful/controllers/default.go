// auther:  yongming.li
package controllers
import (
        _ "github.com/Go-SQL-Driver/MySQL"
	"github.com/astaxie/beego"
        "encoding/json"
        "fmt"
        "github.com/astaxie/beego/orm"
        "database/sql"
)
////////////////////////////////////////////////////////////////////////
type User struct {
	userid      string
	name       string
	password    string
        email       string
}

func myinit() {
	// 需要在init中注册定义的model
	orm.RegisterModel(new(User))
        orm.RegisterDriver("mysql", orm.DR_MySQL)
	orm.RegisterDataBase("mynode", "mysql", "root:123456@/alluser?charset=utf8", 30)
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
func (this * MainController) Post() {
      var s Serverslice
   s.Servers = append(s.Servers, Server{ServerName: "Shanghai_VPN", ServerIP: "127.0.0.1"})
   s.Servers = append(s.Servers, Server{ServerName: "Beijing_VPN", ServerIP: "127.0.0.2"})
   b, err := json.Marshal(s)
   if err != nil {
   fmt.Println("json err:", err)
   }
   b=b
   //this.Ctx.WriteString("lizi")
   this.Ctx.WriteString(string(b))
   return
}

type Userinfo struct {
UserName string
UserID   string 
UserEmail   string
}
type Userinfoslice struct {
Userinfos []Userinfo
}

func (this * MainController) Get() {

   
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

	db, err := sql.Open("mysql", "root:123456@/mynode?charset=utf8")
	//checkErr(err)
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
	rows, err := db.Query("SELECT userid , name , email FROM alluser")
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
                u.Userinfos = append(u.Userinfos, Userinfo{UserName: name, UserID: userid,UserEmail:email})
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

	db.Close()

}

type Nodeinfo struct {
 NodeID   string 
}
type Nodeinfoslice struct {
Nodeinfos []Nodeinfo
}

type NodeController struct {
     beego.Controller
}
func (this * NodeController) Get() {

        var node Nodeinfoslice
        var name string 
        var userid string
        var str string
        name = this.Ctx.Input.Param(":username")
        str= "name is " + name;
        fmt.Println(str)
	db, err := sql.Open("mysql", "root:123456@/mynode?charset=utf8")
        //this.Ctx.WriteString("hello")
        //return
        checkErr(err)
        str = "SELECT userid FROM alluser WHERE name="+"'"+name+"'"
        rows, err := db.Query(str)
        fmt.Println(str)
        checkErr(err)
        for rows.Next() {
		err = rows.Scan(&userid)
		checkErr(err)
                fmt.Println("userid is "+userid)
                break;
	}
	// 查询数据
        str = "SELECT nodeid FROM node where userid =" + "'"+userid+"'"
        fmt.Println(str)
	rows, err = db.Query(str)
	checkErr(err)
	for rows.Next() {
		var nodeid string
		err = rows.Scan(&nodeid)
		checkErr(err)
                node.Nodeinfos = append(node.Nodeinfos, Nodeinfo{NodeID: nodeid })
	}
           b, err := json.Marshal(node)
	   if err != nil {
	   fmt.Println("json err:", err)
	   }
	   this.Ctx.WriteString(string(b))
	   db.Close()
}
func checkErr(err error) {
	if err != nil {
	panic(err)
	}
}


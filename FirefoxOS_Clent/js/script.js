//md5
(function($){var rotateLeft=function(lValue,iShiftBits){return(lValue << iShiftBits)|(lValue >>>(32 - iShiftBits));}var addUnsigned=function(lX,lY){var lX4,lY4,lX8,lY8,lResult;lX8=(lX & 0x80000000);lY8=(lY & 0x80000000);lX4=(lX & 0x40000000);lY4=(lY & 0x40000000);lResult=(lX & 0x3FFFFFFF)+(lY & 0x3FFFFFFF);if(lX4 & lY4)return(lResult ^ 0x80000000 ^ lX8 ^ lY8);if(lX4 | lY4){if(lResult & 0x40000000)return(lResult ^ 0xC0000000 ^ lX8 ^ lY8);else return(lResult ^ 0x40000000 ^ lX8 ^ lY8);} else {return(lResult ^ lX8 ^ lY8);}}var F=function(x,y,z){return(x & y)|((~ x)& z);}var G=function(x,y,z){return(x & z)|(y &(~ z));}var H=function(x,y,z){return(x ^ y ^ z);}var I=function(x,y,z){return(y ^(x |(~ z)));}var FF=function(a,b,c,d,x,s,ac){a=addUnsigned(a,addUnsigned(addUnsigned(F(b,c,d),x),ac));return addUnsigned(rotateLeft(a,s),b);};var GG=function(a,b,c,d,x,s,ac){a=addUnsigned(a,addUnsigned(addUnsigned(G(b,c,d),x),ac));return addUnsigned(rotateLeft(a,s),b);};var HH=function(a,b,c,d,x,s,ac){a=addUnsigned(a,addUnsigned(addUnsigned(H(b,c,d),x),ac));return addUnsigned(rotateLeft(a,s),b);};var II=function(a,b,c,d,x,s,ac){a=addUnsigned(a,addUnsigned(addUnsigned(I(b,c,d),x),ac));return addUnsigned(rotateLeft(a,s),b);};var convertToWordArray=function(string){var lWordCount;var lMessageLength=string.length;var lNumberOfWordsTempOne=lMessageLength + 8;var lNumberOfWordsTempTwo=(lNumberOfWordsTempOne -(lNumberOfWordsTempOne % 64))/ 64;var lNumberOfWords=(lNumberOfWordsTempTwo + 1)* 16;var lWordArray=Array(lNumberOfWords - 1);var lBytePosition=0;var lByteCount=0;while(lByteCount<lMessageLength){lWordCount=(lByteCount -(lByteCount % 4))/ 4;lBytePosition=(lByteCount % 4)* 8;lWordArray[lWordCount]=(lWordArray[lWordCount] |(string.charCodeAt(lByteCount)<< lBytePosition));lByteCount++;}lWordCount=(lByteCount -(lByteCount % 4))/ 4;lBytePosition=(lByteCount % 4)* 8;lWordArray[lWordCount]=lWordArray[lWordCount] |(0x80 << lBytePosition);lWordArray[lNumberOfWords - 2]=lMessageLength << 3;lWordArray[lNumberOfWords - 1]=lMessageLength>>>29;return lWordArray;};var wordToHex=function(lValue){var WordToHexValue="",WordToHexValueTemp="",lByte,lCount;for(lCount=0; lCount <= 3; lCount++){lByte=(lValue >>>(lCount * 8))& 255;WordToHexValueTemp="0" + lByte.toString(16);WordToHexValue=WordToHexValue + WordToHexValueTemp.substr(WordToHexValueTemp.length - 2,2);}return WordToHexValue;};var uTF8Encode=function(string){string=string.replace(/\x0d\x0a/g,"\x0a");var output="";for(var n=0; n<string.length; n++){var c=string.charCodeAt(n);if(c<128){output += String.fromCharCode(c);} else if((c > 127)&&(c<2048)){output += String.fromCharCode((c >> 6)| 192);output += String.fromCharCode((c & 63)| 128);} else {output += String.fromCharCode((c >> 12)| 224);output += String.fromCharCode(((c >> 6)& 63)| 128);output += String.fromCharCode((c & 63)| 128);}}return output;};$.md5=function(string){var x=Array();var k,AA,BB,CC,DD,a,b,c,d;var S11=7,S12=12,S13=17,S14=22;var S21=5,S22=9 ,S23=14,S24=20;var S31=4,S32=11,S33=16,S34=23;var S41=6,S42=10,S43=15,S44=21;string=uTF8Encode(string);x=convertToWordArray(string);a=0x67452301; b=0xEFCDAB89; c=0x98BADCFE; d=0x10325476;for(k=0; k<x.length; k += 16){AA=a; BB=b; CC=c; DD=d;a=FF(a,b,c,d,x[k+0],S11,0xD76AA478);d=FF(d,a,b,c,x[k+1],S12,0xE8C7B756);c=FF(c,d,a,b,x[k+2],S13,0x242070DB);b=FF(b,c,d,a,x[k+3],S14,0xC1BDCEEE);a=FF(a,b,c,d,x[k+4],S11,0xF57C0FAF);d=FF(d,a,b,c,x[k+5],S12,0x4787C62A);c=FF(c,d,a,b,x[k+6],S13,0xA8304613);b=FF(b,c,d,a,x[k+7],S14,0xFD469501);a=FF(a,b,c,d,x[k+8],S11,0x698098D8);d=FF(d,a,b,c,x[k+9],S12,0x8B44F7AF);c=FF(c,d,a,b,x[k+10],S13,0xFFFF5BB1);b=FF(b,c,d,a,x[k+11],S14,0x895CD7BE);a=FF(a,b,c,d,x[k+12],S11,0x6B901122);d=FF(d,a,b,c,x[k+13],S12,0xFD987193);c=FF(c,d,a,b,x[k+14],S13,0xA679438E);b=FF(b,c,d,a,x[k+15],S14,0x49B40821);a=GG(a,b,c,d,x[k+1],S21,0xF61E2562);d=GG(d,a,b,c,x[k+6],S22,0xC040B340);c=GG(c,d,a,b,x[k+11],S23,0x265E5A51);b=GG(b,c,d,a,x[k+0],S24,0xE9B6C7AA);a=GG(a,b,c,d,x[k+5],S21,0xD62F105D);d=GG(d,a,b,c,x[k+10],S22,0x2441453);c=GG(c,d,a,b,x[k+15],S23,0xD8A1E681);b=GG(b,c,d,a,x[k+4],S24,0xE7D3FBC8);a=GG(a,b,c,d,x[k+9],S21,0x21E1CDE6);d=GG(d,a,b,c,x[k+14],S22,0xC33707D6);c=GG(c,d,a,b,x[k+3],S23,0xF4D50D87);b=GG(b,c,d,a,x[k+8],S24,0x455A14ED);a=GG(a,b,c,d,x[k+13],S21,0xA9E3E905);d=GG(d,a,b,c,x[k+2],S22,0xFCEFA3F8);c=GG(c,d,a,b,x[k+7],S23,0x676F02D9);b=GG(b,c,d,a,x[k+12],S24,0x8D2A4C8A);a=HH(a,b,c,d,x[k+5],S31,0xFFFA3942);d=HH(d,a,b,c,x[k+8],S32,0x8771F681);c=HH(c,d,a,b,x[k+11],S33,0x6D9D6122);b=HH(b,c,d,a,x[k+14],S34,0xFDE5380C);a=HH(a,b,c,d,x[k+1],S31,0xA4BEEA44);d=HH(d,a,b,c,x[k+4],S32,0x4BDECFA9);c=HH(c,d,a,b,x[k+7],S33,0xF6BB4B60);b=HH(b,c,d,a,x[k+10],S34,0xBEBFBC70);a=HH(a,b,c,d,x[k+13],S31,0x289B7EC6);d=HH(d,a,b,c,x[k+0],S32,0xEAA127FA);c=HH(c,d,a,b,x[k+3],S33,0xD4EF3085);b=HH(b,c,d,a,x[k+6],S34,0x4881D05);a=HH(a,b,c,d,x[k+9],S31,0xD9D4D039);d=HH(d,a,b,c,x[k+12],S32,0xE6DB99E5);c=HH(c,d,a,b,x[k+15],S33,0x1FA27CF8);b=HH(b,c,d,a,x[k+2],S34,0xC4AC5665);a=II(a,b,c,d,x[k+0],S41,0xF4292244);d=II(d,a,b,c,x[k+7],S42,0x432AFF97);c=II(c,d,a,b,x[k+14],S43,0xAB9423A7);b=II(b,c,d,a,x[k+5],S44,0xFC93A039);a=II(a,b,c,d,x[k+12],S41,0x655B59C3);d=II(d,a,b,c,x[k+3],S42,0x8F0CCC92);c=II(c,d,a,b,x[k+10],S43,0xFFEFF47D);b=II(b,c,d,a,x[k+1],S44,0x85845DD1);a=II(a,b,c,d,x[k+8],S41,0x6FA87E4F);d=II(d,a,b,c,x[k+15],S42,0xFE2CE6E0);c=II(c,d,a,b,x[k+6],S43,0xA3014314);b=II(b,c,d,a,x[k+13],S44,0x4E0811A1);a=II(a,b,c,d,x[k+4],S41,0xF7537E82);d=II(d,a,b,c,x[k+11],S42,0xBD3AF235);c=II(c,d,a,b,x[k+2],S43,0x2AD7D2BB);b=II(b,c,d,a,x[k+9],S44,0xEB86D391);a=addUnsigned(a,AA);b=addUnsigned(b,BB);c=addUnsigned(c,CC);d=addUnsigned(d,DD);}var tempValue=wordToHex(a)+ wordToHex(b)+ wordToHex(c)+wordToHex(d);return tempValue.toLowerCase();};})(Zepto);
//JSON
(function($){'use strict';var escape=/["\\\x00-\x1f\x7f-\x9f]/g,meta={'\b':'\\b','\t':'\\t','\n':'\\n','\f':'\\f','\r':'\\r','"':'\\"','\\':'\\\\'},hasOwn=Object.prototype.hasOwnProperty;$.toJSON=typeof JSON==='object'&&JSON.stringify?JSON.stringify:function(o){if(o===null){return'null'};var pairs,k,name,val,type=$.type(o);if(type==='undefined'){return undefined};if(type==='number'||type==='boolean'){return String(o)};if(type==='string'){return $.quoteString(o)};if(typeof o.toJSON==='function'){return $.toJSON(o.toJSON())};if(type==='date'){var month=o.getUTCMonth()+1,day=o.getUTCDate(),year=o.getUTCFullYear(),hours=o.getUTCHours(),minutes=o.getUTCMinutes(),seconds=o.getUTCSeconds(),milli=o.getUTCMilliseconds();if(month<10){month='0'+month};if(day<10){day='0'+day};if(hours<10){hours='0'+hours};if(minutes<10){minutes='0'+minutes};if(seconds<10){seconds='0'+seconds};if(milli<100){milli='0'+milli};if(milli<10){milli='0'+milli};return'"'+year+'-'+month+'-'+day+'T'+hours+':'+minutes+':'+seconds+'.'+milli+'Z"'};pairs=[];if($.isArray(o)){for(k=0;k<o.length;k++){pairs.push($.toJSON(o[k])||'null')};return'['+pairs.join(',')+']'};if(typeof o==='object'){for(k in o){if(hasOwn.call(o,k)){type=typeof k;if(type==='number'){name='"'+k+'"'}else if(type==='string'){name=$.quoteString(k)}else{continue};type=typeof o[k];if(type!=='function'&&type!=='undefined'){val=$.toJSON(o[k]);pairs.push(name+':'+val)}}};return'{'+pairs.join(',')+'}'}};$.evalJSON=typeof JSON==='object'&&JSON.parse?JSON.parse:function(str){return eval('('+str+')')};$.secureEvalJSON=typeof JSON==='object'&&JSON.parse?JSON.parse:function(str){var filtered=str.replace(/\\["\\\/bfnrtu]/g,'@').replace(/"[^"\\\n\r]*"|true|false|null|-?\d+(?:\.\d*)?(?:[eE][+\-]?\d+)?/g,']').replace(/(?:^|:|,)(?:\s*\[)+/g,'');if(/^[\],:{}\s]*$/.test(filtered)){return eval('('+str+')')};throw new SyntaxError('Error parsing JSON, source is not valid.')};$.quoteString=function(str){if(str.match(escape)){return'"'+str.replace(escape,function(a){var c=meta[a];if(typeof c==='string'){return c};c=a.charCodeAt();return'\\u00'+Math.floor(c/16).toString(16)+(c%16).toString(16)})+'"'};return'"'+str+'"'}}(Zepto));

var storage=window.localStorage,
session=window.sessionStorage,
myinfo=session.getItem('myinfo'),
meurl=window.location.href,
sh={
	nowLogin:-1,
	auth:{},
	/*
	 * 初始化
	 * 初始化登录信息、用户基本信息
	 * @param function run 初始化完成运行
	*/
	init:function(run){
		var now=session.getItem('nowLogin'),auth=storage.getItem('auth');
		if (auth!==null) sh.auth=$.parseJSON(auth);
		if (now!==null) sh.nowLogin=now;
		if (sh.auth.length!==0 && sh.nowLogin!=-1) {
			if (myinfo===null) {
				sh.getApi({
					requestType:"get",
					requestData:{"auth":sh.getLogin().auth},
					type:"member",
					action:"getMyInfo",
					error:function(){
						$.alertBox({
							title: "请求失败",
							content: "<p>网络错误</p><p>请检查网络，或刷新后重试</p>",
							style: "default",
							type: "alert",
							okText: "确定",
							okCallback: function() {window.location.reload();}
						});
					},
					success:function(data){
						if (data.success==0) {
							if (data.errcode==1) {
								$.alertBox({
									title: "Auth已过期",
									content: "<p>Auth已过期，请重新登录</p>",
									style: "default",
									type: "alert",
									okText: "确定",
									okCallback: function() {window.location.href='login.html';}
								});
							} else {
								window.location.reload();
							}
							return;
						}
						session.setItem('myinfo',$.toJSON(data));
						myinfo=data;
						run();
					}
				});
			} else {
				try {
					myinfo=$.parseJSON(myinfo);
				} catch(e) {
				}
				run();
			}
		} else {
			run();
		}
	},
	/*
	 * 设置当前登录账号
	 * @param string id 登录信息ID
	*/
	setLogin:function(id){
		session.setItem('nowLogin',id);
		sh.nowLogin=id;
	},
	/*
	 * 获取当前登录账号
	 * @return object 账号信息
	*/
	getLogin:function(){
		console.log($.toJSON(sh.auth[sh.nowLogin]));
		return sh.auth[sh.nowLogin];
	},
	/*
	 * 添加登录账号
	 * @param object info 登录信息
	 * @return string 登录信息ID
	*/
	addAuth:function(info){
		id=$.md5(info.user+'|'+info.host+'|'+info.port);
		if (typeof(sh.auth[id])!=='undefined' && sh.auth[id]!==null) {
			console.log(id+' already exists');
			return id;
		}
		sh.auth[id]=info;
		console.log(sh.auth);
		console.log($.toJSON(sh.auth));
		storage.setItem('auth',$.toJSON(sh.auth));
		return id;
	},
	/*
	 * 移除登录账号
	 * @param string id 登录信息ID
	*/
	removeAuth:function(id){
		if (sh.nowLogin===id) {
			sh.nowLogin=-1;
			session.removeItem('nowLogin');
		}
		delete sh.auth[id];
		storage.setItem('auth',$.toJSON(sh.auth));
	},
	/*
	 * 请求API
	 * @param object option 各种参数
	 * @param boolean option[isCloud] 是否为云控制
	 * @param string option[requestType] 请求类型，GET或者POST，不区分大小写
	 * @param string option[host] 服务器地址，如果没有此参数，则自动从当前登录账号获取
	 * @param string option[port] 服务器端口，如果没有此参数，则自动从当前登录账号获取
	 * @param object option[requestData] 请求数据
	 * @param string option[type] API类型
	 * @param string option[action] API名称
	 * @param function option[error] 失败回调函数
	 * @param function option[success] 失败回调函数
	*/
	getApi:function(option){
		var url,success=option.success,fail=option.error,myload,auth=sh.getLogin();
		if (option.isCloud) {
			return;
			// url='http://server.smarthome.sylingd.com/api/';
		} else {
			url='http://';
			if (typeof(option.host)==='undefined' || option.host===null) url+=auth.host;
			else url+=option.host;
			url+=':';
			if (typeof(option.port)==='undefined' || option.port===null) url+=auth.port;
			else url+=option.port;
			url+='/api/';
		}
		url+=option.type+'/'+option.action+'.json?_r='+new Date().getTime();
		console.log(url);
		myload=$.loadingBox({
			style: "icon",
			icon: "refresh",
			spin: true
		});
		$.ajax({
			"url":url,
			"data":option.requestData,
			"dataType":"text",
			"type":option.requestType.toUpperCase(),
			"error":function(){
				$(myload).hide();
				$('#bg').hide();
				console.error('Fail to get data,URL:'+url);
				if (fail!==null) fail();
			},
			"success":function(data){
				$(myload).hide();
				$('#bg').hide();
				try {
					data=$.parseJSON(data);
				} catch(e) {
					throw new Error('Fail to parse JSON:'+data);
					window.location.reload();
				}
				success(data);
			}
		});
	}
};
sh.init(function(){
	//非登录页
	if (meurl.indexOf('login')<0) {
		if (sh.auth.length===0) { //没有登录任何账号
			window.location.href='login.html';
		} else {
			if (sh.nowLogin==-1) { //需要选择登录账号
				window.location.href='login-choose.html';
			} else {
				$('#myname').append('<span>'+myinfo.name+'</span>');
			}
		}
	}
	//登录页
	if (meurl.indexOf('login.html')>=0) {
		if (sh.auth.length!==0) { //有已登录的账号
			$('.content').append('<a href="login-choose.html" class="btn btn-default btn-block">选择已登录的账号</a>');
		}
		if (sh.nowLogin!=-1) { //已经选择登录的账号
			$('.content').append('<a href="index.html" class="btn btn-default btn-block">返回首页</a>');
		}
	}
	//首页
	if (meurl.indexOf('index.html')>=0) {
		var appto='<h4 data-i18n="index-welcome">'+myinfo.name+'</h4>';
		$('#page1').find('.content').append(appto);
		i18n.setAllLanguage();
	}
	//节点
	if (meurl.indexOf('node.html')>=0) {
		sh.getApi({
			requestType:"get",
			requestData:{"auth":sh.getLogin().auth,"full":0},
			type:"node",
			action:"getMyGroup",
			error:function(){
				$.alertBox({
					title: "请求失败",
					content: "<p>网络错误</p><p>请检查网络，或刷新后重试</p>",
					style: "default",
					type: "alert",
					okText: "确定",
					okCallback: function() {window.location.reload();}
				});
			},
			success:function(data){
				if (data.success==0) {
					$.alertBar(data.errmsg,'warning',2000);
					return;
				}
				var appto='';
				$('#page1').find('.content').html(appto);
			}
		});
	}
	//登录页
	if (meurl.indexOf('login-local.html')>=0) { //本地登录
		$('#login-submit').bind('tap click',function(){
			var shost=$('#host').val(),sport=$('#port').val(),username=$('#user').val(),pwd=$('#password').val();
			sh.getApi({
				isCloud:false,
				requestType:"post",
				host:shost,
				port:sport,
				requestData:{user:username,password:pwd},
				type:"member",
				action:"login",
				error:function(){
					$.alertBox({
						title: "请求失败",
						content: "<p>网络错误</p><p>请检查网络，或稍后再试</p>",
						style: "default",
						type: "alert",
						okText: "确定",
						okCallback: function() {}
					});
				},
				success:function(data){
					var id;
					if (data.success==0) {
						$.alertBar(data.errmsg,'warning',2000);
						return;
					}
					data.user=username;
					data.host=shost;
					data.port=sport;
					data.isCloud=false;
					id=sh.addAuth(data);
					sh.setLogin(id);
					window.location.href='index.html';
				}
			});
		});
	}
	//选择已登录的账号
	if (meurl.indexOf('login-choose.html')>=0) {
		for (var i in sh.auth) {
			if (sh.auth[i].isCloud) $('#cloud').append('<li class="item" data-id="'+i+'">'+sh.auth[i].user+'</li>');
			else $('#local').append('<li class="item" data-id="'+i+'">'+sh.auth[i].user+'@'+sh.auth[i].host+':'+sh.auth[i].port+'</li>');
		}
		$('#local,#cloud').find('.item').bind('tap click',function(){
			sh.setLogin($(this).attr('data-id'));
			window.location.href='index.html';
		});
	}
});
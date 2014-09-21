var i18n={
	lang:{
		"login-local":"本地登录",
		"login-cloud":"云登录",
		"login-submit":"登录",
		"server-host":"服务器地址",
		"server-port":"服务器端口",
		"server-username":"用户名",
		"server-password":"密码",
		"index-welcome":"欢迎您，",
		"login-choose":"选择账号",
		"account-local":"本地账号",
		"account-cloud":"云账号",
		"mynode":"我的节点"
	},
	setLanguage:function(language){
		$('head').append('<script src="i18n/language/'+language+'.js"></script>');
	},
	get:function(key){
		return i18n.lang[key];
	},
	setElementLanguage:function(e){
		e=$(e);
		if ($(e).attr('data-i18n-init')==='o') return;
		if (e.is('title')) {
			document.title=i18n.get($(e).attr('data-i18n'));
			$(e).attr('data-i18n-init','o');
			return;
		}
		if (e.is('input')) {
			$(e).attr('value',i18n.get($(e).attr('data-i18n')));
			$(e).attr('data-i18n-init','o');
			return;
		}
		$(e).prepend(i18n.get($(e).attr('data-i18n')));
		$(e).attr('data-i18n-init','o');
	},
	setAllLanguage:function(){
	$('html').find('[data-i18n]').each(function(i,n){
		i18n.setElementLanguage(n);
	});
	}
};
(function($){
	i18n.setLanguage('zh-CN');
	i18n.setAllLanguage();
})(Zepto);
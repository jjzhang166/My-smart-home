$('#test').switcher();
//测试：alertBar
$('#alerttest-default').tap(function(){$.alertBar('Default test','default',1000);});
$('#alerttest-success').tap(function(){$.alertBar('Success test','success',1000);});
$('#alerttest-danger').tap(function(){$.alertBar('Danger test','danger',1000);});
//测试：alertBox
$('#alertbox1').tap(function(){
	$.alertBox({
		title:"提示框测试",
		content:"<p>这是一个提示框</p><p>这是一个提示框</p>",
		style:"default",
		type:"comfirm",
		okText:"确定",
		cancelText:"取消",
		okCallback:function(){alert('你点击了确定');},
		cancelCallback:function(){alert('你点击了取消');}
	});
});
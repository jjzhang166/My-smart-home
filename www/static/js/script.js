$('#side-menu').metisMenu();
$(window).bind("load resize", function() {
	width=(this.window.innerWidth>0)?this.window.innerWidth:this.screen.width;
	if (width<768) {
		$('div.sidebar-collapse').addClass('collapse')
	} else {
		$('div.sidebar-collapse').removeClass('collapse')
	}
});
$('.dosure').click(function(){
	var to=$(this).attr('data-url');
	if (confirm(suretext)) window.location.href=to;
});
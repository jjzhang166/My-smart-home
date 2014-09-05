;(function($){
	"use strict"
	//自动标题栏宽度
	$('.titlebar').each(function(i,n){
		var hasWidth=0,allWidth=$(n).offset().width;
		$(n).children().each(function(ic,nc){
			if (!$(nc).hasClass('title')) hasWidth+=$(nc).offset().width;
		});
		console.log(hasWidth);
		console.log(allWidth);
		$(n).children('.title').css({
			width: (allWidth-hasWidth-30).toString() + 'px'
		});
	});
	//组件：开关
	$.fn.switcher = function(action) {
		var element;
		//打开开关
		if (action === 'on') {
			if ($(this).data('fooso-initswitcher') !== 'done') throw new Error('Switcher not inited yet');
			element = $(this).data('fooso-switcher');
			$(element).addClass('on');
			this.checked = true;
		}
		//关闭开关
		if (action === 'off') {
			if ($(this).data('fooso-initswitcher') !== 'done') throw new Error('Switcher not inited yet');
			element = $(this).data('fooso-switcher');
			$(element).removeClass('on');
			this.checked = false;
		}
		//建立开关
		element = document.createElement('div');
		if ($(this).data('fooso-initswitcher') === 'done') return $(this).data('fooso-switcher');
		if (this.checked) $(element).addClass('on');
		$(element).addClass('switcher');
		$(element).html('<div class="line"></div><div class="button">&nbsp;</div>');
		$(this).hide();
		$(this).before(element);
		$(this).data('fooso-initswitcher', 'done');
		$(this).data('fooso-switcher', element);
		$(element).data('fooso-box', this);
		$(element).bind('tap',
		function() {
			$(this).toggleClass('on');
			if ($(this).hasClass('on')) {
				$(this).data('fooso-box').checked = true;
			} else {
				$(this).data('fooso-box').checked = false;
			}
		});
		return element;
	}

	//组件：提示条
	$.alertBar = function(msg, type, hide) {
		var ele = document.createElement('div');
		$(ele).html(msg);
		$(ele).addClass('alertBar');
		$(ele).addClass('alert-' + type);
		$(ele).css({
			opacity: 0
		});
		$('body').append(ele);
		$(ele).animate({
			opacity: 1
		},
		100);
		if (hide > 100) {
			setTimeout(function() {
				$(ele).animate({
					opacity: 0
				},
				100);
			},
			hide - 100);
		}
		setTimeout(function() {
			$(ele).hide();
		},
		hide);
	}
	//组件：提示框
	$.alertBox = function(option) {
		var ele = document.createElement('div'),
		btn = document.createElement('div'),
		btn1 = document.createElement('input'),
		btn2 = document.createElement('input'),
		hideAlertBox;
		hideAlertBox = function() {
			$(this).parents('.alertBox').hide();
			$('#bg').hide();
		}
		$(ele).addClass('alertBox');
		$(ele).addClass('alertBox-' + option.style);
		if (typeof(option.title) !== 'undefined' && option.title !== '' && option.title !== null) { //是否有标题
			$(ele).append('<div class="alertBox-title">' + option.title + '</div>');
		}
		if (typeof(option.okText) === 'undefined' || option.okText === '' || option.okText === null) { //确认按钮
			option.okText = '确认';
		}
		if (typeof(option.cancelText) === 'undefined' || option.cancelText === '' || option.cancelText === null) { //取消按钮
			option.cancelText = '取消';
		}
		$(ele).addClass('alert-' + option.css);
		$(ele).append('<div class="alertBox-content">' + option.content + '</div>');
		//提示框按钮
		$(btn).addClass('alertBox-btn');
		if (option.type === 'alert') { //提示框，只有一个确认按钮
			$(btn).addClass('alertBox-oneBtn');
		} else { //确认、取消，两个按钮
			$(btn).addClass('alertBox-twoBtn');
			$(btn2).attr('value', option.cancelText);
			$(btn2).on('tap', hideAlertBox);
			$(btn2).on('tap', option.cancelCallback);
			$(btn).append(btn2);
		}
		$(btn1).attr('value', option.okText);
		$(btn1).on('tap', hideAlertBox);
		$(btn1).on('tap', option.okCallback);
		$(btn).append(btn1);
		$(ele).append(btn);
		$('#bg').show();
		$('body').append(ele);
		$(ele).css({
			marginTop: '-' + ($(ele).height() / 2).toString() + 'px'
		});
	}
	//标题栏和菜单
	$('.btn-back').tap(function() {
		var to = $(this).attr('data-to');
		if (to === 'url') {
			window.location.href = $(this).attr('data-url');
			return;
		}
		if (to ==='page') {
		
		}
	});

	$('.btn-menu').bind('click',
	function() {
		var menu = $($(this).attr('data-menu'));
		menu.animate({
			left: 0
		},
		100);
		$('#bg').show();
		$('#bg').tap(function() {
			var thewidth = '-' + menu.width().toString() + 'px';
			menu.animate({
				left: thewidth
			},
			100);
			$('#bg').unbind('tap');
			$('#bg').hide();
		});
	});
	$('.menu').each(function(i, n) {
		var menu = $(n),
		thewidth = '-' + menu.width().toString() + 'px';
		menu.css({
			left: thewidth
		});
	});
	$('.menu').find('.item a').bind('tap',
	function() {
		var item = $(this).parents('.item'),
		fa = $(this).find('.more');
		fa.removeClass('fa-angle-left').removeClass('fa-angle-down');
		if (item.attr('data-toggle') === 'dropdown') { //展开列表
			if (item.hasClass('active')) fa.addClass('fa-angle-left');
			else fa.addClass('fa-angle-down');
			item.toggleClass('active');
		}
	});

	//下拉刷新

})(Zepto)
; (function($) {
	"use strict";
	var fooso = {
		pull: {
			top: 0,
			startX: 0,
			startY: 0
		}
	};
	//自动标题栏宽度
	$('.titlebar').each(function(i, n) {
		var hasWidth = 0,
		allWidth = $(n).offset().width;
		$(n).children().each(function(ic, nc) {
			if (!$(nc).hasClass('title')) hasWidth += $(nc).offset().width;
		});
		$(n).children('.title').css({
			width: (allWidth - hasWidth - 30).toString() + 'px'
		});
	});
	//组件：开关
	$.fn.switcher = function(action) {
		var element;
		//打开开关
		if (action === 'on') {
			if ($(this).data('fooso-initswitcher') !== 'done') throw new Error('Switcher not inited yet');
			element = $(this).data('fooso-switcher');
			if ($(element).hasClass('disabled')) return; //禁用状态
			$(element).addClass('on');
			this.checked = true;
			return element;
		}
		//关闭开关
		if (action === 'off') {
			if ($(this).data('fooso-initswitcher') !== 'done') throw new Error('Switcher not inited yet');
			element = $(this).data('fooso-switcher');
			if ($(element).hasClass('disabled')) return; //禁用状态
			$(element).removeClass('on');
			this.checked = false;
			return element;
		}
		//禁用开关
		if (action === 'disable') {
			if ($(this).data('fooso-initswitcher') !== 'done') throw new Error('Switcher not inited yet');
			element = $(this).data('fooso-switcher');
			$(element).addClass('disabled');
			return element;
		}
		//启用开关
		if (action === 'able') {
			if ($(this).data('fooso-initswitcher') !== 'done') throw new Error('Switcher not inited yet');
			element = $(this).data('fooso-switcher');
			$(element).removeClass('disabled');
			return element;
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
			if ($(this).hasClass('disabled')) return; //禁用状态
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
		200);
		if (hide > 200) {
			setTimeout(function() {
				$(ele).animate({
					opacity: 0
				},
				200);
			},
			hide - 200);
		}
		setTimeout(function() {
			$(ele).hide();
		},
		hide);
	}
	//组件：加载框
	$.loadingBox = function(option) {
		var ele = document.createElement('div');
		$(ele).addClass('loadingBox').addClass('loadingBox-' + option.style);
		if (typeof(option.icon) !== 'undefined' && option.icon !== '' && option.icon !== null) { //是否有图标
			if (option.spin) $(ele).append('<div class="icon"><i class="fa fa-spin fa-' + option.icon + '"></i></div>');
			else $(ele).append('<div class="icon"><i class="fa fa-' + option.icon + '"></i></div>');
		}
		if (typeof(option.text) !== 'undefined' && option.text !== '' && option.text !== null) $(ele).append('<div class="text">' + option.text + '</div>');
		$('#bg').show();
		$('body').append(ele);
		return ele;
	}
	//组件：提示框
	$.alertBox = function(option) {
		var ele = document.createElement('div'),
		btn = document.createElement('div'),
		btn1 = document.createElement('input'),
		btn2,
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
		$(ele).append('<div class="alertBox-content">' + option.content + '</div>');
		//提示框按钮
		$(btn).addClass('alertBox-btn');
		if (option.type === 'alert') { //提示框，只有一个确认按钮
			$(btn).addClass('alertBox-oneBtn');
		} else { //确认、取消，两个按钮
			$(btn).addClass('alertBox-twoBtn');
			btn2 = document.createElement('input');
			$(btn2).attr('value', option.cancelText);
			$(btn2).attr('type', 'button');
			$(btn2).bind('tap', hideAlertBox);
			$(btn2).bind('tap', option.cancelCallback);
			$(btn).append(btn2);
		}
		$(btn1).attr('value', option.okText);
		$(btn1).attr('type', 'button');
		$(btn1).bind('tap', hideAlertBox);
		$(btn1).bind('tap', option.okCallback);
		$(btn).append(btn1);
		$(ele).append(btn);
		$('#bg').show();
		$('body').append(ele);
		$(ele).css({
			marginTop: '-' + ($(ele).height() / 2).toString() + 'px'
		});
	}
	//跳页相关
	$.goPage = function(pageid) {
		if ($('#page' + pageid).length) {
			$('.page-show').removeClass('page-show');
			$('#page' + pageid).addClass('page-show');
		} else {
			throw new Error('Page ' + pageid + ' Not exists');
		}
	}
	//标题栏和菜单
	$('.btn-back').bind('tap',
	function() {
		var to = $(this).attr('data-to');
		if (to === 'url') {
			window.location.href = $(this).attr('data-url');
			return;
		}
		if (to === 'page') {
			$.goPage($(this).attr('data-page'));
			return;
		}
	});

	$('.btn-menu').bind('click',
	function() {
		var menu = $($(this).attr('data-menu'));
		menu.css({
			left: 0
		});
		$('#bg').show();
		$('#bg').tap(function() {
			var thewidth = '-' + menu.width().toString() + 'px';
			menu.css({
				left: thewidth
			});
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
		if (item.attr('data-toggle') === 'dropdown') { //展开列表
			item.toggleClass('active');
			fa.toggleClass('fa-rotate-90');
		}
	});
	$('.menu').find('.item').find('.more').addClass('fa-rotate-90');
	$('.menu').find('.active').find('.more').removeClass('fa-rotate-90');

	//下拉和上拉
	$.fn.pull = function(option) {
		var pullEle, pullType;
		if ($.inArray(option.type, ['up', 'down']) < 0) throw new Error('Pull need param "type" and "type" must is "up" or "down"');
		pullType = option.type.replace(/^(\w)/,
		function(s) {
			return s.toUpperCase();
		});
		if (typeof(option.text) === 'undefined' || option.text === '' || option.text === null) { //文本
			if (option.type == 'up') option.text = '上拉加载更多';
			else option.text = '下拉加载更多';
		}
		if (typeof(option.loadingText) === 'undefined' || option.loadingText === '' || option.loadingText === null) { //加载中文本
			option.loadingText = '加载中';
		}
		if (typeof(option.style) === 'undefined' || option.style === '' || option.style === null) { //加载中文本
			option.style = 'default';
		}
		pullEle = document.createElement('div');
		$(pullEle).addClass('pull').addClass('pull-' + option.style);
		//是否有图标
		if ($.inArray(option.icon, ['spinner', 'refresh']) >= 0) $(pullEle).append('<i class="loading fa fa-' + option.icon + '"></i>');
		$(pullEle).append('<span class="pullText">' + option.text + '</span>');
		//绑定
		$(this).data('fooso-pull' + pullType + 'Option', option);
		$(this).data('fooso-pull' + pullType, pullEle);
		//将pull元素添加进去
		if (option.type == 'up') $(this).append(pullEle);
		else $(this).prepend(pullEle);
		$(this).bind('touchstart',
		function(e) {
			var touch = touch = (e.targetTouches[0] ? e.targetTouches[0] : (e.touches[0] ? e.touches[0] : e));
			fooso.pull.top = $(this).parents('.page')[0].scrollTop;
			fooso.pull.startX = touch.pageX;
			fooso.pull.startY = touch.pageY;
		});
		$(this).bind('touchend',
		function(e) {
			var mePullType, top = fooso.pull.top,
			startX = fooso.pull.startX,
			startY = fooso.pull.startY,
			touch = (e.targetTouches[0] ? e.targetTouches[0] : (e.touches[0] ? e.touches[0] : e)),
			endX = touch.pageX,
			endY = touch.pageY,
			pull = this,
			mepull = $($(pull).data('fooso-pull' + pullType)),
			option = $(this).data('fooso-pull' + pullType + 'Option'),
			finish = function() {
				var me = $(pull);
				$(me.data('fooso-pull' + pullType)).find('.pullText').html(me.data('fooso-pull' + pullType + 'Option').text);
				$(me.data('fooso-pull' + pullType)).find('.loading').removeClass('fa-spin');
			};
			if ((Math.abs(endX - startX) > Math.abs(endY - startY)) || Math.abs(endY - startY) < 20) { //并非上下滑动或滑动距离太小
				return;
			}
			console.log(endY);
			if (Math.abs(top - $(this).parents('.page')[0].scrollTop) < 20) { //非滚动
				if (endY < startY) mePullType = 'Up';
				else mePullType = 'Down';
				if (mePullType == pullType) {
					mepull.find('.pullText').html(option.loadingText);
					mepull.find('.loading').addClass('fa-spin'); //转起来
					option.callback(this, finish);
				}
			}
		});
	}

})(Zepto)
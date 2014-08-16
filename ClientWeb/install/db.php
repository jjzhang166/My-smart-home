<?php
/*
 * 最新数据库设计，包括SQL和NoSQL部分
*/
$sql=array();
/*
 * 节点表：node
 * id bigint(10) 自动生成的节点ID
 * type smallint(6) 所属节点组
*/
$sql['node']='CREATE TABLE `#@__node` (
	`id` bigint(10) AUTO_INCREMENT,
	`type` smallint(6) NOT NULL,
	PRIMARY KEY(`id`),
	INDEX(`type`)
)ENGINE=MyISAM DEFAULT CHARSET=utf8 AUTO_INCREMENT=1;';
/*
 * NoSQL节点：node_id
 * name string 名称
 * command ??
 * value ??
*/
/*
 * 用户表：user
 * id bigint(10) 用户ID
 * type smallint(6) 对应的用户组
 * name varchar(20) 用户名
 * email varchar(255) 邮箱
 * isAdmin int(1) 是否为管理员，1为是
*/
$sql['user']='CREATE TABLE `#@__user` (
	`id` bigint(10) AUTO_INCREMENT,
	`type` smallint(6) NOT NULL,
	`name` varchar(50) NOT NULL,
	`password` char(32) NOT NULL,
	`email` varchar(255) NOT NULL,
	`isAdmin` int(1) NOT NULL DEFAULT \'0\',
	PRIMARY KEY(`id`),
	INDEX(`type`),
	INDEX(`name`),
	INDEX(`isAdmin`),
	INDEX(`email`)
)ENGINE=MyISAM DEFAULT CHARSET=utf8 AUTO_INCREMENT=1;';
/*
 * Auth表：auth
 * auth char(32) 不解释
 * uid bigint(10) 用户ID
 * overdue date 过期时间
*/
$sql['auth']='CREATE TABLE `#@__auth` (
	`auth` char(32) NOT NULL,
	`uid` bigint(10) NOT NULL,
	`overdue` date NOT NULL,
	PRIMARY KEY(`auth`),
	INDEX(`overdue`)
)ENGINE=MyISAM DEFAULT CHARSET=utf8 AUTO_INCREMENT=1;';
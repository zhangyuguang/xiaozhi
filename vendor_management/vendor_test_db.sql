-- phpMyAdmin SQL Dump
-- version 3.5.2.2
-- http://www.phpmyadmin.net
--
-- 主机: 127.0.0.1
-- 生成日期: 2016 年 10 月 14 日 03:06
-- 服务器版本: 5.5.27-log
-- PHP 版本: 5.4.6

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- 数据库: `vendor`
--

-- --------------------------------------------------------

--
-- 表的结构 `info`
--

CREATE TABLE IF NOT EXISTS `info` (
  `id` int(8) NOT NULL AUTO_INCREMENT,
  `st_info` varchar(255) NOT NULL,
  `st_addr` varchar(255) NOT NULL,
  `st_type` varchar(255) NOT NULL,
  `off_info` varchar(255) NOT NULL,
  `item_info` varchar(255) NOT NULL,
  `item_type` varchar(255) NOT NULL,
  `date` varchar(255) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `id` (`id`),
  KEY `id_2` (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=3 ;

--
-- 转存表中的数据 `info`
--

INSERT INTO `info` (`id`, `st_info`, `st_addr`, `st_type`, `off_info`, `item_info`, `item_type`, `date`) VALUES
(1, 'xxx', 'xxx', 'xxx', 'xxx', 'xxx', 'xxx', 'xxx'),
(2, 'yyy', 'yyy', '??', 'yyy', 'yyy', '??', 'yyyyyy');

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;

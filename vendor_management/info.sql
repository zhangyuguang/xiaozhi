-- phpMyAdmin SQL Dump
-- version 3.5.2.2
-- http://www.phpmyadmin.net
--
-- 主机: 127.0.0.1
-- 生成日期: 2016 年 10 月 15 日 05:24
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
  `st_info` varchar(255) CHARACTER SET utf8 NOT NULL,
  `st_addr` varchar(255) CHARACTER SET utf8 NOT NULL,
  `st_type` varchar(255) CHARACTER SET utf8 NOT NULL,
  `off_info` varchar(255) CHARACTER SET utf8 NOT NULL,
  `item_info` varchar(255) CHARACTER SET utf8 NOT NULL,
  `item_type` varchar(255) CHARACTER SET utf8 NOT NULL,
  `date` varchar(255) CHARACTER SET utf8 NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `id` (`id`),
  KEY `id_2` (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=6 ;

--
-- 转存表中的数据 `info`
--

INSERT INTO `info` (`id`, `st_info`, `st_addr`, `st_type`, `off_info`, `item_info`, `item_type`, `date`) VALUES
(1, '虾兵蟹将', '奇峰路735-23号', '美食', '6-8折', '岛城第一家虾兵蟹将海鲜大咖，人均200元', '海鲜', '2016-10-31'),
(2, '土豪餐厅', '巨峰路与南崂路交界处，李沧万达广场1号门旁', '美食', '减20-50元', '炒菜，人均72元', '川菜', '2016-12-31'),
(3, '海底捞火锅（万达广场店）', '万达广场 巨峰路178号万达广场6楼', '美食', '返现20-30元', '火锅，人均108元', '火锅', '2016-12-31'),
(4, '品秀量贩式KTV(李沧万达店)', '巨峰路万达广场二楼(原万达大歌星)', 'KTV', '15元/20元/30元套餐', '欢畅2小时', 'KTV', '2016-10-20'),
(5, '万达国际影城(李沧店)', '巨峰路148号万达广场3楼万达影城', '电影', '10元套餐/15元套餐', '电影票+小份可乐+小份爆米花', '电影', '2016-10-18');

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;

-- phpMyAdmin SQL Dump
-- version 4.1.6
-- http://www.phpmyadmin.net
--
-- Host: 127.0.0.1
-- Generation Time: 2014-06-29 12:00:00
-- 服务器版本： 5.6.16
-- PHP Version: 5.5.9

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Database: `lishunan`
--

-- --------------------------------------------------------

--
-- 表的结构 `lecture`
--

CREATE TABLE IF NOT EXISTS `lecture` (
  `lid` int(11) NOT NULL AUTO_INCREMENT,
  `ltype` varchar(30) NOT NULL,
  `classroom` varchar(30) NOT NULL,
  `lname` varchar(30) NOT NULL,
  `tid` int(11) NOT NULL,
  `credit` float NOT NULL,
  `day` int(11) NOT NULL,
  `time` int(11) NOT NULL,
  PRIMARY KEY (`lid`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=7 ;

--
-- 转存表中的数据 `lecture`
--

INSERT INTO `lecture` (`lid`, `ltype`, `classroom`, `lname`, `tid`, `credit`, `day`, `time`) VALUES
(2, '通识', '西1 203', 'English', 3, 2.5, 3, 3),
(3, '通识', '西1 203', 'English', 31, 2.5, 3, 3),
(4, '通识', '西1 203', 'English', 32, 2.5, 3, 3),
(5, '通识', '西1 203', 'English', 33, 2.5, 3, 3),
(6, '通识2', '西1 203', 'English', 3, 2.5, 3, 3);

-- --------------------------------------------------------

--
-- 表的结构 `people`
--

CREATE TABLE IF NOT EXISTS `people` (
  `username` varchar(30) NOT NULL,
  `password` varchar(30) NOT NULL,
  `type` varchar(30) NOT NULL,
  `uid` int(11) NOT NULL AUTO_INCREMENT,
  PRIMARY KEY (`uid`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=8 ;

--
-- 转存表中的数据 `people`
--

INSERT INTO `people` (`username`, `password`, `type`, `uid`) VALUES
('student', 'student', 'student', 1),
('dfdf', 'dffd', 'student', 2),
('teacher', 'teacher', 'teacher', 3),
('dsfgdsg', 'dfgdsg', 'student', 5),
('student', 'student', 'student', 6),
('', '', 'student', 7);

-- --------------------------------------------------------

--
-- 表的结构 `take`
--

CREATE TABLE IF NOT EXISTS `take` (
  `tid` int(11) NOT NULL AUTO_INCREMENT,
  `lid` int(11) NOT NULL,
  `uid` int(11) NOT NULL,
  `grade` int(11) DEFAULT NULL,
  PRIMARY KEY (`tid`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8mb4 AUTO_INCREMENT=7 ;

--
-- 转存表中的数据 `take`
--

INSERT INTO `take` (`tid`, `lid`, `uid`, `grade`) VALUES
(1, 2, 1, 30),
(2, 2, 2, 22),
(3, 2, 5, NULL),
(4, 2, 5, NULL);

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;

-- MySQL dump 8.23
--
-- Host: localhost    Database: webhavenx
---------------------------------------------------------
-- Server version	3.23.58

--
-- Table structure for table `cashbook`
--

DROP TABLE IF EXISTS cashbook;
CREATE TABLE cashbook (
  id int(10) NOT NULL auto_increment,
  account_id int(10) NOT NULL default '0',
  type_id int(10) NOT NULL default '0',
  owner_id int(10) NOT NULL default '0',
  date_entered timestamp(14) NOT NULL,
  date_modified date NOT NULL default '0000-00-00',
  transaction_date date NOT NULL default '0000-00-00',
  status varchar(55) NOT NULL default '',
  value_inclusive decimal(10,2) NOT NULL default '0.00',
  value_exclusive decimal(10,2) NOT NULL default '0.00',
  gst_rate decimal(4,3) NOT NULL default '0.00',
  notes text NOT NULL,
  PRIMARY KEY  (id)
) TYPE=MyISAM PACK_KEYS=0;

--
-- Table structure for table `cashbook_log`
--

CREATE TABLE IF NOT EXISTS `cashbook_log` (
  `id` int(10) NOT NULL AUTO_INCREMENT,
  `input_method` varchar(55) NOT NULL DEFAULT '',
  `ref` varchar(55) NOT NULL DEFAULT '',
  `account_id` int(10) NOT NULL DEFAULT '0',
  `type_id` int(10) NOT NULL DEFAULT '0',
  `owner_id` int(10) NOT NULL DEFAULT '0',
  `employee_id` int(10) NOT NULL DEFAULT '0',
  `date_entered` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  `date_modified` date NOT NULL DEFAULT '0000-00-00',
  `transaction_date` date NOT NULL DEFAULT '0000-00-00',
  `status` varchar(55) NOT NULL DEFAULT '',
  `gst_rate` decimal(4,3) NOT NULL,
  `value_inclusive` decimal(10,2) NOT NULL DEFAULT '0.00',
  `value_exclusive` decimal(10,2) NOT NULL DEFAULT '0.00',
  `gst` decimal(10,2) NOT NULL DEFAULT '0.00',
  `notes` text NOT NULL,
  PRIMARY KEY (`id`)
);

--
-- Table structure for table `cashbook_accounts`
--

DROP TABLE IF EXISTS cashbook_accounts;
CREATE TABLE cashbook_accounts (
  id int(10) NOT NULL auto_increment,
  name varchar(55) NOT NULL default '',
  gst tinyint(1) NOT NULL default '0',
  PRIMARY KEY  (id)
) TYPE=MyISAM;

--
-- Table structure for table `cashbook_types`
--

DROP TABLE IF EXISTS cashbook_types;
CREATE TABLE cashbook_types (
  id int(10) NOT NULL auto_increment,
  name varchar(55) NOT NULL default '',
  PRIMARY KEY  (id)
) TYPE=MyISAM;


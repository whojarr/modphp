-- MySQL dump 8.23
--
-- Host: localhost    Database: webhaven
---------------------------------------------------------
-- Server version	3.23.58

--
-- Table structure for table `tasks`
--

DROP TABLE IF EXISTS tasks;
CREATE TABLE tasks (
  id int(11) NOT NULL auto_increment,
  parent int(11) default NULL,
  title text,
  notes text,
  url text NOT NULL,
  status varchar(55) default NULL,
  priority int(4) default '3',
  date_due date NOT NULL default '2004-01-31',
  date_modified timestamp(14) NOT NULL,
  date_entered timestamp(14) NOT NULL,
  type smallint(6) NOT NULL default '0',
  date_bill date NOT NULL default '2004-01-31',
  owner_id int(11) NOT NULL default '1',
  duration int(11) NOT NULL default '0',
  accountmanager int(11) NOT NULL default '1',
  billable int(4) NOT NULL default '0',
  budget int(11) default '0',
  cost int(11) default '0',
  value decimal(5,2) default '0.00',
  PRIMARY KEY  (id),
  KEY id (id),
  KEY parent (parent),
  KEY type (type),
  KEY owner (owner_id),
  KEY accountmanager (accountmanager)
) TYPE=MyISAM;

--
-- Table structure for table `tasks_groups`
--

DROP TABLE IF EXISTS tasks_groups;
CREATE TABLE tasks_groups (
  task_id int(11) NOT NULL default '0',
  group_id int(11) NOT NULL default '0',
  KEY task_id (task_id),
  KEY group_id (group_id)
) TYPE=MyISAM;

--
-- Table structure for table `tasks_modules`
--

DROP TABLE IF EXISTS tasks_modules;
CREATE TABLE tasks_modules (
  task_id int(11) NOT NULL default '0',
  module_id int(11) NOT NULL default '0',
  KEY task_id (task_id)
) TYPE=MyISAM;


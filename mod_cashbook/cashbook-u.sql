ALTER TABLE `cashbook` ADD `gst_rate` DECIMAL( 4, 3 ) NOT NULL AFTER `status`;
ALTER TABLE `cashbook_log` ADD `gst_rate` DECIMAL( 4, 3 ) NOT NULL AFTER `status`;
UPDATE cashbook SET gst_rate = '0.125' WHERE transaction_date < '2010-10-01';

UPDATE cashbook
SET gst_rate = '0.00'
WHERE account_id NOT IN (
   SELECT id 
   FROM cashbook_accounts
   WHERE gst = '1'
);

UPDATE cashbook SET value_exclusive = value_inclusive WHERE gst_rate = 0.00;

UPDATE cashbook SET value_inclusive = ROUND(value_exclusive * 1.125,2) WHERE value_inclusive = 0.00 AND value_exclusive <> 0.00 AND gst_rate > 0;
UPDATE cashbook SET value_inclusive = value_exclusive WHERE value_inclusive = 0.00 AND value_exclusive <> 0.00 AND gst_rate = 0.00;
UPDATE cashbook SET value_exclusive = ROUND(value_inclusive - (value_inclusive/9),2) WHERE value_exclusive = 0.00 AND value_inclusive <> 0.00 AND gst_rate > 0;
UPDATE cashbook SET value_exclusive = value_inclusive WHERE value_exclusive = 0.00 AND value_inclusive <> 0.00 AND gst_rate = 0.00;

-- Update log table to use same selct from cashbook query but allow duplicate id entries.
ALTER TABLE `cashbook_log` CHANGE `id` `id` INT( 10 ) NOT NULL; 
ALTER TABLE `cashbook_log` DROP PRIMARY KEY;
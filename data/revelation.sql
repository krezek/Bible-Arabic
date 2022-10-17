DROP TABLE IF EXISTS revelation;
CREATE VIRTUAL TABLE revelation USING FTS5(chapter, verse, prefix, suffix, body);

.read revelation/revelation_1.sql
.read revelation/revelation_2.sql
.read revelation/revelation_3.sql
.read revelation/revelation_4.sql
.read revelation/revelation_5.sql
.read revelation/revelation_6.sql
.read revelation/revelation_7.sql
.read revelation/revelation_8.sql
.read revelation/revelation_9.sql
.read revelation/revelation_10.sql
.read revelation/revelation_11.sql
.read revelation/revelation_12.sql
.read revelation/revelation_13.sql
.read revelation/revelation_14.sql
.read revelation/revelation_15.sql
.read revelation/revelation_16.sql
.read revelation/revelation_17.sql
.read revelation/revelation_18.sql
.read revelation/revelation_19.sql
.read revelation/revelation_20.sql
.read revelation/revelation_21.sql
.read revelation/revelation_22.sql

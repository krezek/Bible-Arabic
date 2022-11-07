DROP TABLE IF EXISTS judges;
CREATE VIRTUAL TABLE judges USING FTS5(chapter, verse, prefix, suffix, body);

.read judges/judges_1.sql
.read judges/judges_2.sql
.read judges/judges_3.sql
.read judges/judges_4.sql
.read judges/judges_5.sql
.read judges/judges_6.sql
.read judges/judges_7.sql
.read judges/judges_8.sql
.read judges/judges_9.sql
.read judges/judges_10.sql
.read judges/judges_11.sql
.read judges/judges_12.sql
.read judges/judges_13.sql
.read judges/judges_14.sql
.read judges/judges_15.sql
.read judges/judges_16.sql
.read judges/judges_17.sql
.read judges/judges_18.sql
.read judges/judges_19.sql
.read judges/judges_20.sql
.read judges/judges_21.sql

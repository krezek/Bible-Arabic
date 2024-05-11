DROP TABLE IF EXISTS matthew_sy;
CREATE VIRTUAL TABLE matthew_sy USING FTS5(chapter, verse, prefix, suffix, body);

.read matthew/matthew_1.sql
.read matthew/matthew_2.sql
.read matthew/matthew_3.sql
/*.read matthew/matthew_4.sql
.read matthew/matthew_5.sql
.read matthew/matthew_6.sql
.read matthew/matthew_7.sql
.read matthew/matthew_8.sql
.read matthew/matthew_9.sql
.read matthew/matthew_10.sql
.read matthew/matthew_11.sql
.read matthew/matthew_12.sql
.read matthew/matthew_13.sql
.read matthew/matthew_14.sql
.read matthew/matthew_15.sql
.read matthew/matthew_16.sql
.read matthew/matthew_17.sql
.read matthew/matthew_18.sql
.read matthew/matthew_19.sql
.read matthew/matthew_20.sql
.read matthew/matthew_21.sql
.read matthew/matthew_22.sql
.read matthew/matthew_23.sql
.read matthew/matthew_24.sql
.read matthew/matthew_25.sql
.read matthew/matthew_26.sql
.read matthew/matthew_27.sql
.read matthew/matthew_28.sql*/

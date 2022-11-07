DROP TABLE IF EXISTS hosea;
CREATE VIRTUAL TABLE hosea USING FTS5(chapter, verse, prefix, suffix, body);

.read hosea/hosea_1.sql
.read hosea/hosea_2.sql
.read hosea/hosea_3.sql
.read hosea/hosea_4.sql
.read hosea/hosea_5.sql
.read hosea/hosea_6.sql
.read hosea/hosea_7.sql
.read hosea/hosea_8.sql
.read hosea/hosea_9.sql
.read hosea/hosea_10.sql
.read hosea/hosea_11.sql
.read hosea/hosea_12.sql
.read hosea/hosea_13.sql
.read hosea/hosea_14.sql

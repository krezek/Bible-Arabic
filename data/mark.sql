DROP TABLE IF EXISTS mark;
CREATE VIRTUAL TABLE mark USING FTS5(chapter, verse, prefix, suffix, body);


INSERT INTO mark (chapter, verse, prefix, suffix, body)
VALUES (1, 1, NULL, NULL, "بَدْءُ إِنْجِيلِ يَسُوعَ الْمَسِيحِ ابْنِ اللهِ،");

INSERT INTO mark (chapter, verse, prefix, suffix, body)
VALUES (1, 2, NULL, NULL, "كَمَا هُوَ مَكْتُوبٌ فِي الأَنْبِيَاءِ: «هَا أَنَا أُرْسِلُ أَمَامَ وَجْهِكَ مَلاَكِي، الَّذِي يُهَيِّئُ طَرِيقَكَ قُدَّامَكَ.");

INSERT INTO mark (chapter, verse, prefix, suffix, body)
VALUES (1, 3, NULL, NULL, "صَوْتُ صَارِخٍ فِي الْبَرِّيَّةِ: أَعِدُّوا طَرِيقَ الرَّبِّ، اصْنَعُوا سُبُلَهُ مُسْتَقِيمَةً».");



INSERT INTO mark (chapter, verse, prefix, suffix, body)
VALUES (2, 1, NULL, NULL, "ثُمَّ دَخَلَ كَفْرَنَاحُومَ أَيْضًا بَعْدَ أَيَّامٍ، فَسُمِعَ أَنَّهُ فِي بَيْتٍ.");

INSERT INTO mark (chapter, verse, prefix, suffix, body)
VALUES (2, 2, NULL, NULL, "وَلِلْوَقْتِ اجْتَمَعَ كَثِيرُونَ حَتَّى لَمْ يَعُدْ يَسَعُ وَلاَ مَا حَوْلَ الْبَابِ. فَكَانَ يُخَاطِبُهُمْ بِالْكَلِمَةِ.");

INSERT INTO mark (chapter, verse, prefix, suffix, body)
VALUES (2, 3, NULL, NULL, "وَجَاءُوا إِلَيْهِ مُقَدِّمِينَ مَفْلُوجًا يَحْمِلُهُ أَرْبَعَةٌ.");

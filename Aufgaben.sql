1.
    SELECT DISTINCT ort
    FROM gast JOIN besucht ON besucher_nname = nname AND besucher_vname = vname
    JOIN biergarten ON bname = biergarten_name
    WHERE lieblingsgetraenk =  'Pils';

2.
    SELECT ort, AVG(preisproliter)
    FROM biergarten JOIN schenkt_aus On bname = biergarten_name
    JOIN getraenk On gname = getraenke_name
    WhERE alkogehalt > 0
    GROUP BY ort;

3.
    SELECT ort, AVG(preisproliter)
    FROM biergarten JOIN schenkt_aus On bname = biergarten_name
    JOIN getraenk On gname = getraenke_name
    WHERE alkogehalt > 0
    GROUP BY ort
    HAVING SUM(ausschankprotag) > 1500;

4.
    SELECT bname
    FROM biergarten
    WHERE umsatzprojahr > (SELECT umsatzprojahr 
                           FROM biergarten
                           WHERE bname = 'Zur letzten Instanz' AND ort = 'Vilsbiburg')
    ORDER BY bname desc;

5a.
    SELECT DISTINCT vname || ' ' || nname AS name, lieblingsgetraenk
    FROM gast JOIN besucht ON vname = besucher_vname AND nname = besucher_nname
    JOIN biergarten ON bname = biergarten_name
    WHERE bname > 'Fimstuben'
    ORDER BY name asc;

5b.
    SELECT DISTINCT vname || ' ' || nname AS name, lieblingsgetraenk
    FROM gast JOIN besucht ON vname = besucher_vname AND nname = besucher_nname
    JOIN biergarten ON bname = biergarten_name
    WHERE bname > ALL (SELECT bname
                       FROM biergarten JOIN schenkt_aus ON bname = biergarten_name
                       WHERE getraenke_name = 'Lauwasser')
    ORDER BY name asc;

6a.
    SELECT gname
    FROM getraenk
    EXCEPT
    SELECT lieblingsgetraenk FROM gast;

6b.
    SELECT gname
    FROM getraenk
    WHERE gname NOT IN (SELECT lieblingsgetraenk FROM gast);

6c.
    SELECT gname
    FROM getraenk
    WHERE NOT EXISTS (SELECT lieblingsgetraenk FROM gast WHERE lieblingsgetraenk = gname);

7.
    create table ortsstatistik (
        stat_ort char(20),
        anz_biergarten int,
        durchschnitt_umsatz decimal(8,2)
    );

    INSERT INTO ortsstatistik
    SELECT ort, COUNT(*), SUM(umsatzprojahr)
    FROM biergarten
    GROUP BY ort;

8.
    UPDATE biergarten
    SET anzahlplaetze = (SELECT MAX(anzahlplaetze) FROM biergarten)
    WHERE bname IN (SELECT bname
                  FROM gast JOIN besucht ON nname = besucher_nname AND vname = besucher_vname
                  JOIN biergarten ON biergarten_name = bname
                  WHERE gebdatum < '1.1.1945');

9.
    DELETE FROM schenkt_aus
    WHERE getraenke_name IN (SELECT gname FROM getraenk WHERE hersteller NOT IN (SELECT hersteller from getraenk JOIN gast ON lieblingsgetraenk = gname));

    DELETE FROM getraenk
    WHERE hersteller IN (SELECT hersteller FROM getraenk WHERE hersteller NOT IN (SELECT hersteller from getraenk JOIN gast ON lieblingsgetraenk = gname));

    DELETE FROM firma
    WHERE fname NOT IN (SELECT DISTINCT hersteller FROM getraenk WHERE gname IN (SELECT lieblingsgetraenk FROM gast));

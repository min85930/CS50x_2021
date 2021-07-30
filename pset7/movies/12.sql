SELECT tA.title
FROM (
    SELECT movies.title
    FROM movies
    JOIN stars ON movies.id = stars.movie_id
    JOIN people ON stars.person_id = people.id
    WHERE people.name = 'Johnny Depp') as tA
INNER JOIN (
    SELECT movies.title
    FROM movies
    JOIN stars ON movies.id = stars.movie_id
    JOIN people ON stars.person_id = people.id
    WHERE people.name = 'Helena Bonham Carter') as tB
ON tA.title = tB.title;
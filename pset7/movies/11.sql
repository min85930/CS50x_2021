SELECT movies.title
FROM stars
JOIN people ON stars.person_id = people.id
JOIN movies ON stars.movie_id = movies.id
JOIN ratings ON stars.movie_id = ratings.movie_id
WHERE people.name = 'Chadwick Boseman'
ORDER BY ratings.rating DESC
LIMIT 5;
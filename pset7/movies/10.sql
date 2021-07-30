SELECT DISTINCT(people.name) 
FROM directors 
JOIN ratings ON directors.movie_id = ratings.movie_id 
JOIN people ON people.id = directors.person_id 
WHERE ratings.rating >= 9.0;
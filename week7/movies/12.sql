SELECT title FROM movies, people, stars
WHERE movies.id = stars.movie_id
AND movies.id = stars.movie_id
AND people.id = stars.person_id
AND (people.name = 'Bradley Cooper'
OR people.name = 'Jennifer Lawrence');
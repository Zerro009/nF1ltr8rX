import { useNavigate } from 'react-router-dom'

import style from './link.module.scss'

export const Link = ({route, children}) => {
	const navigate = useNavigate()

	return (
		<div
			className={style.link}
			onClick={() => navigate(route)}
		>
			{children}
		</div>
	)
}

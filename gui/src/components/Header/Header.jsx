import axios from 'axios'
import { Link } from '../Link/Link'

import style from './header.module.scss'

export const Header = () => {
	const url = 'http://192.168.199.9:8001/'
	axios.get(url)
		.then((res) => {
			console.log(res.data)
		}).catch(err => {
			console.log(err)
		})

	return (
		<div className={style.header}>
			<div className={style.wrapperLogo}>
			</div>
			<div className={style.wrapperLink}>
				<Link
					route='/home/'
					children='Home'
				/>
				<Link
					route='/mapper/'
					children='Mapper'
				/>
			</div>
		</div>
	)
}

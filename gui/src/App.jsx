import {
	BrowserRouter as Router,
	Routes,
	Route
} from 'react-router-dom'

import { Header } from './components/Header/Header'
import { ScannerForm } from './forms/ScannerForm/ScannerForm'

import style from './app.module.scss'

const App = () => {
	return (
		<Router>
			<div className={style.app}>
				<Header />
				<ScannerForm />
			</div>
		</Router>
	)
}

export default App;
